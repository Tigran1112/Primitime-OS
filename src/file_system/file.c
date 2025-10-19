#include "base/base.h"
#include "screen/screen.h"
#define max_files 200

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
    copy_str(name, fs.files[fs.count].name);
    fs.count++;
}
void delete_file(char name[])
{
    for (int i = 0; i < fs.count; i++)
    {
        if (strcmp(name, fs.files[i].name) == 0)
        {
            for (int j = i; j < fs.count - 1; j++)
            {
                copy_str(fs.files[j+1].name, fs.files[j].name);
                copy_str(fs.files[j+1].data, fs.files[j].data);
            }
            fs.count--;
            clear_str(2);
            replace("File deleted successful", 2, 0x0a);
            return;
        }
    }
    clear_str(2);
    replace("File not found", 2, 0x0a);
}