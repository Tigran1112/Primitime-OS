#include "file_system/file/file.h"
#include "screen/screen.h"
#include "input/strcmp/strcmp.h"

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
