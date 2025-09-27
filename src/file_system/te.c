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

void open_file(char name[]) {
    int index = -1;
    
    for (int j = 0; j < fs.count; j++) 
    {
        if (strcmp(fs.files[j].name, name) == 0) 
        {
            index = j;
            break;
        }
    }
    
    if (index == -1) 
    {
        replace("File not found", 1, 0x0C);
        return;
    }
    
    replace(fs.files[index].data, 1, 0x0A);
}
