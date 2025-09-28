#define NULL ((void*)0)

int strcmp(const char *s1, const char *s2) 
{
    while (*s1 && *s2 && *s1 == *s2) 
    {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

int strncmp(const char *s1, const char *s2, int n) 
{
    for (int i = 0; i < n; i++) 
    {
        if (s1[i] != s2[i]) return s1[i] - s2[i];
        if (s1[i] == '\0') return 0;
    }
    return 0;
}

char *strchr(const char *str, int ch)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == ch) return (char*)&str[i];
    }
    return NULL;
}

// Добавляем недостающие функции
char *strcpy(char *dest, const char *src)
{
    char *d = dest;
    while (*src) {
        *d++ = *src++;
    }
    *d = '\0';
    return dest;
}
void copy_str(const char *src, char *dest)
{
    int i = 0;
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}
void trim(char *str)
{
    char *end = str;
    while (*end != '\0') end++;
    end--;
    while (end > str && (*end == ' ' || *end == '\t')) 
    {
        *end = '\0';
        end--;
    }
    
    char *start = str;
    while (*start == ' ' || *start == '\t') start++;
    
    if (start != str)
    {
        char *d = str;
        while (*start)
        {
            *d++ = *start++;
        }
        *d = '\0';
    }
}