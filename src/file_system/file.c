#include "base/base.h"
#include "screen/screen.h"
#include <stdint.h>
#include <stdbool.h>

#define max_files 200
#define max_name 128
#define max_data 1024
#define disk_size 0x10000
#define block_size 512

typedef struct
{
    char name[max_name];
    uint32_t offset;
    uint32_t size;
    bool used;
} file;

typedef struct
{
    file files[max_files];
    uint8_t disk[disk_size];
} file_system;

file_system fs;

void sfs_init(file_system *fs)
{

}
int sfs_create(file_system *fs, const char *name, uint16_t size)
{

}
int sfs_delete(file_system *fs, const char *name)
{

}
int sfs_write(file_system *fs, const char *name, uint8_t *data, uint32_t size)
{

}
int sfs_read(file_system *fs, const char *name, uint8_t *buffer, uint32_t buf_size)
{
    
}