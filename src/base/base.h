#ifndef BASE_H
#define BASE_H

int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, int n);
char *strchr(const char *str, int ch);
void copy_str(const char *src, char *dest);
void trim(char *str);
int rand();

#endif