#include <stdbool.h>
#include "input/power/power.h"
#include "file_system/file.h"
#include "screen/screen.h"
#include "input/strcmp/strcmp.h"
#include "games/racer.h"

#define NULL ((void*)0)

int mode = 0;

void standart_exec(char cmd[])
{
    clear();
    for (int i = 1; i < 8; i++)
    {
        clear_str(i);
    }

    if (strncmp(cmd, "write", 5) == 0) 
    {
        replace(&cmd[5], 3, 0x0a);
    }
    else if(strcmp(cmd, "list") == 0)
    {
        if (fs.count == 0)
        {
            replace("Files not found", 2, 0x0a);
        }
        else
        {
            for (int i = 0; i < fs.count; i++)
            {
                replace(fs.files[i].name, i+2, 0x0a);
            }
        }
    }
    else if (strncmp(cmd, "make ", 5) == 0) 
    {
        if (cmd[5] != '\0' && cmd[5] != ' ')
        {
            create_file(&cmd[5]);
            replace("File created", 2, 0x0a);
        }
        else
        {
            replace("Please enter file name", 2, 0x0a);
        }
    }
    else if (strncmp(cmd, "dlt ", 4) == 0)
    {
        char *name = &cmd[4];
        delete_file(name);
    }
    else if (strncmp(cmd, "te ", 3) == 0)
    {
        char *name = &cmd[3];
        char *text = strchr(name, ' ');

        if (text == NULL) 
        {
            for (int i = 0; i < fs.count; i++) 
            {
                if (strcmp(name, fs.files[i].name) == 0) 
                {
                    print(fs.files[i].data, 1, 0x0a);
                    return;
                }
            }
            replace("File not found", 1, 0x0a);
            return;
        }
        
        *text = '\0';
        text++;
        
        int is_found = -1;
        for (int i = 0; i < fs.count; i++)
        {
            if (strcmp(fs.files[i].name, name) == 0)
            {
                is_found = i;
                break;
            }
        }
        
        if (is_found == -1)
        {
            replace("File not found", 2,0x0a);
            return;
        }
        if (text != 0) copy_str(text, fs.files[is_found].data);
        replace("File updated succesful", 2, 0x0a);
    }
    else if (strcmp(cmd, "shutdown") == 0)
    {
        replace("Shutdown...", 0, 0x0a);
        shutdown();
    }
    else if (strcmp(cmd, "reload") == 0)
    {
        replace("Rebooting...", 0, 0x0a);
        reboot();
    }
    else if (strcmp(cmd, "racer") == 0)
    {
        mode = 1;
        init_racer();
    }
    else if (strcmp(cmd, "hello") == 0) 
    {
        replace("Hello. Welcome to PrimitiveOS by Tigrics.", 1, 0x0a);
    }
    else if (strcmp(cmd, "help") == 0) 
    {
        char commands[][100] = {
            "hello - hello message", 
            "clear - clear console", 
            "help - list commands", 
            "write [text] - print text",
            "make [file] - create file",
            "dlt [file] - delete file",
            "list - show files",
            "te [file] [text] - text editor",
            "shutdown - shutdown system",
            "reload - reload system",
        };
        
        int count = sizeof(commands) / sizeof(commands[0]);
        
        for (int i = 0; i < count; i++)
        {
            replace(commands[i], i + 1, 0x0a);
        }
    }
    else if (strcmp(cmd, "clear") == 0) 
    {
        clear();
    }
    else 
    {
        replace("command not found", 1, 0x0a);
    }
}
void game_exec(char cmd[])
{
    if (!racer_running) return;

    if (strcmp(cmd, "a") == 0)
    {
        racer_move_left();
    }
    else if (strcmp(cmd, "d") == 0)
    {
        racer_move_right();
    }
    else if (strcmp(cmd, "w") == 0)
    {
        racer_move_forward();
    }
    
    else
    {
        mode = 0;
        clear();
    }
}
void exec(char cmd[]) 
{
    switch (mode)
    {
        case 0:
            standart_exec(cmd);
        break;
        case 1:
            game_exec(cmd);
        break;
    }
}