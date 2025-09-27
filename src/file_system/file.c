#include <stdbool.h>
#define MAX_FILES 200

struct File
{
    char name[256];
    char data[2048];
    int size;
    bool is_directory;
};
struct file_system
{
    struct File files[128];
    int count;
};

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
struct file_system fs;

void create_file(char name[])
{
    copy_str(name, fs.files[fs.count].name);
    fs.count++;
}