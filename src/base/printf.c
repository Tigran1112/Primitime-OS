#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>

#include "printf.h"

#define NTOA_BUFFER_SIZE 32U

#define FLAGS_ZEROPAD   (1U << 0U)
#define FLAGS_LEFT      (1U << 1U)
#define FLAGS_PLUS      (1U << 2U)
#define FLAGS_SPACE     (1U << 3U)
#define FLAGS_HASH      (1U << 4U)
#define FLAGS_UPPERCASE (1U << 5U)
#define FLAGS_PRECISION (1U << 6U)

static unsigned int _strnlen_s(const char* str, size_t maxsize) {
    const char* s;
    for (s = str; *s && maxsize--; ++s);
    return (unsigned int)(s - str);
}

static inline bool _is_digit(char ch) {
    return (ch >= '0') && (ch <= '9');
}

static unsigned int _atoi(const char** str) {
    unsigned int i = 0U;
    while (_is_digit(**str)) {
        i = i * 10U + (unsigned int)(*((*str)++) - '0');
    }
    return i;
}

static size_t _out_rev(char* buffer, size_t idx, size_t maxlen, const char* buf, size_t len, unsigned int width, unsigned int flags) {
    const size_t start_idx = idx;

    if (!(flags & FLAGS_LEFT) && !(flags & FLAGS_ZEROPAD)) {
        for (size_t i = len; i < width; i++) {
            if (idx < maxlen) buffer[idx++] = ' ';
        }
    }

    while (len) {
        if (idx < maxlen) buffer[idx++] = buf[--len];
    }

    if (flags & FLAGS_LEFT) {
        while (idx - start_idx < width) {
            if (idx < maxlen) buffer[idx++] = ' ';
        }
    }

    return idx;
}

static size_t _ntoa_format(char* buffer, size_t idx, size_t maxlen, char* buf, size_t len, bool negative, unsigned int base, unsigned int prec, unsigned int width, unsigned int flags) {
    if (!(flags & FLAGS_LEFT)) {
        if (width && (flags & FLAGS_ZEROPAD) && (negative || (flags & (FLAGS_PLUS | FLAGS_SPACE)))) {
            width--;
        }
        while ((len < prec) && (len < NTOA_BUFFER_SIZE)) {
            buf[len++] = '0';
        }
        while ((flags & FLAGS_ZEROPAD) && (len < width) && (len < NTOA_BUFFER_SIZE)) {
            buf[len++] = '0';
        }
    }

    if (len < NTOA_BUFFER_SIZE) {
        if (negative) {
            buf[len++] = '-';
        }
        else if (flags & FLAGS_PLUS) {
            buf[len++] = '+';
        }
        else if (flags & FLAGS_SPACE) {
            buf[len++] = ' ';
        }
    }

    return _out_rev(buffer, idx, maxlen, buf, len, width, flags);
}

static size_t _ntoa_long(char* buffer, size_t idx, size_t maxlen, unsigned long value, bool negative, unsigned long base, unsigned int prec, unsigned int width, unsigned int flags) {
    char buf[NTOA_BUFFER_SIZE];
    size_t len = 0U;

    if (!(flags & FLAGS_PRECISION) || value) {
        do {
            const char digit = (char)(value % base);
            buf[len++] = digit < 10 ? '0' + digit : (flags & FLAGS_UPPERCASE ? 'A' : 'a') + digit - 10;
            value /= base;
        } while (value && (len < NTOA_BUFFER_SIZE));
    }

    return _ntoa_format(buffer, idx, maxlen, buf, len, negative, (unsigned int)base, prec, width, flags);
}

static int _vsnprintf(char* buffer, const size_t maxlen, const char* format, va_list va) {
    unsigned int flags, width, precision;
    size_t idx = 0U;

    while (*format && idx < maxlen) {
        if (*format != '%') {
            buffer[idx++] = *format++;
            continue;
        } else {
            format++;
        }

        flags = 0U;
        do {
            switch (*format) {
                case '0': flags |= FLAGS_ZEROPAD; format++; break;
                case '-': flags |= FLAGS_LEFT;    format++; break;
                case '+': flags |= FLAGS_PLUS;    format++; break;
                case ' ': flags |= FLAGS_SPACE;   format++; break;
                case '#': flags |= FLAGS_HASH;    format++; break;
                default : break;
            }
        } while (0);

        width = 0U;
        if (_is_digit(*format)) {
            width = _atoi(&format);
        } else if (*format == '*') {
            const int w = va_arg(va, int);
            width = (w < 0) ? (unsigned int)-w : (unsigned int)w;
            if (w < 0) flags |= FLAGS_LEFT;
            format++;
        }

        precision = 0U;
        if (*format == '.') {
            flags |= FLAGS_PRECISION;
            format++;
            if (_is_digit(*format)) {
                precision = _atoi(&format);
            } else if (*format == '*') {
                const int prec = (int)va_arg(va, int);
                precision = prec > 0 ? (unsigned int)prec : 0U;
                format++;
            }
        }

        switch (*format) {
            case 'd':
            case 'i':
            case 'u':
            case 'x':
            case 'X':
            case 'o': {
                unsigned int base;
                if (*format == 'x' || *format == 'X') {
                    base = 16U;
                } else if (*format == 'o') {
                    base = 8U;
                } else {
                    base = 10U;
                    flags &= ~FLAGS_HASH;
                }
                
                if (*format == 'X') {
                    flags |= FLAGS_UPPERCASE;
                }

                if ((*format != 'i') && (*format != 'd')) {
                    flags &= ~(FLAGS_PLUS | FLAGS_SPACE);
                }

                if (flags & FLAGS_PRECISION) {
                    flags &= ~FLAGS_ZEROPAD;
                }

                if ((*format == 'i') || (*format == 'd')) {
                    const int value = va_arg(va, int);
                    idx = _ntoa_long(buffer, idx, maxlen, 
                                  (unsigned long)(value > 0 ? value : -value), 
                                  value < 0, base, precision, width, flags);
                } else {
                    const unsigned int value = va_arg(va, unsigned int);
                    idx = _ntoa_long(buffer, idx, maxlen, value, false, base, precision, width, flags);
                }
                format++;
                break;
            }

            case 'c': {
                unsigned int l = 1U;
                if (!(flags & FLAGS_LEFT)) {
                    while (l++ < width && idx < maxlen) {
                        buffer[idx++] = ' ';
                    }
                }
                if (idx < maxlen) {
                    buffer[idx++] = (char)va_arg(va, int);
                }
                if (flags & FLAGS_LEFT) {
                    while (l++ < width && idx < maxlen) {
                        buffer[idx++] = ' ';
                    }
                }
                format++;
                break;
            }

            case 's': {
                const char* p = va_arg(va, char*);
                if (!p) p = "(null)";
                unsigned int l = _strnlen_s(p, precision ? precision : (size_t)-1);
                if (flags & FLAGS_PRECISION) {
                    l = (l < precision ? l : precision);
                }
                if (!(flags & FLAGS_LEFT)) {
                    while (l++ < width && idx < maxlen) {
                        buffer[idx++] = ' ';
                    }
                }
                while (*p != 0 && (!(flags & FLAGS_PRECISION) || precision--) && idx < maxlen) {
                    buffer[idx++] = *(p++);
                }
                if (flags & FLAGS_LEFT) {
                    while (l++ < width && idx < maxlen) {
                        buffer[idx++] = ' ';
                    }
                }
                format++;
                break;
            }

            case '%':
                if (idx < maxlen) buffer[idx++] = '%';
                format++;
                break;

            default:
                if (idx < maxlen) buffer[idx++] = *format;
                format++;
                break;
        }
    }

    if (idx < maxlen) {
        buffer[idx] = '\0';
    } else if (maxlen > 0) {
        buffer[maxlen - 1] = '\0';
    }

    return (int)idx;
}

int sprintf_(char* buffer, const char* format, ...) {
    va_list va;
    va_start(va, format);
    const int ret = _vsnprintf(buffer, (size_t)-1, format, va);
    va_end(va);
    return ret;
}