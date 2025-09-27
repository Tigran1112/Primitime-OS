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
