#ifndef PRINTF_H
#define PRINTF_H

#include <stdarg.h>
#include <stddef.h>

int sprintf_(char* buffer, const char* format, ...);
int vsprintf_(char* buffer, const char* format, va_list va);

#endif