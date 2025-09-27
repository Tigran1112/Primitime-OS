#ifndef FILE_H
#define FILE_H

#define MAX_FILES 200
struct file
{
    char name[256];
    char data[2048];
    int size;
};
struct file_system
{
    struct file files[128];
    int count;
};

void copy_str(const char *src, char *dest);
extern struct file_system fs;
void create_file(char name[]);

#endif