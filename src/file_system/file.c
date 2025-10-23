#include "base/base.h"
#include "file_system/file.h"
#include "screen/screen.h"
#include <stdint.h>
#include <stdbool.h>

#define MAX_FILES 200
struct file
{
    char name[256];
    char data[2048];
};
struct file_system
{
    struct file files[128];
    int count;
};
struct file_system fs;

void create_file(char name[])
{
    copy_str(fs.files[fs.count].name, name);
    fs.count++;
}
void delete_file(char name[])
{
    for (int i = 0; i < fs.count; i++)
    {
        if (strcmp(fs.files[i].name, name) == 0)
        {
            for (int j = i; i < fs.count; j++)
            {
                copy_str(fs.files[j].name, fs.files[j - 1].name);
                copy_str(fs.files[j].data, fs.files[j - 1].data);
            }
        }
        replace("File not found", 0, 0x0a);
    }
}