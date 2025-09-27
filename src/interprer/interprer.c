#include <stdbool.h>
#include "input/power/power.h"
#include "file_system/file/file.h"
#include "screen/screen.h"
#include "input/strcmp/strcmp.h"

bool command_mode = true;

void exec(char cmd[]) 
{
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
            replace("No files", 2, 0x0a);
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
            clear_str(2);
            replace("File created", 2, 0x0a);
        }
        else
        {
            clear_str(2);
            replace("Please enter file name", 2, 0x0a);
        }
    }
    else if (strncmp(cmd, "te ", 3) == 0)
    {
        if (cmd[3] != '\0' && cmd[3] != ' ')
        {
            open_file(&cmd[3]);
            char *result = get_str(1);
            if (strcmp(result, "File not found") != 0)
            {
                command_mode = false;
                clear();
            }
            else
            {
                command_mode = true;
            }
        }
        else
        {
            clear_str(2);
            replace("Please enter file name", 2, 0x0a);
        }
    }
    else if (strcmp(cmd, "shutdown") == 0)
    {
        clear();
        replace("Shutdown...", 0, 0x0a);
        shutdown();
    }
    else if (strcmp(cmd, "reload") == 0)
    {
        clear();
        replace("Rebooting...", 0, 0x0a);
        reboot();
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
            "make [name] - create file",
            "list - show files",
            "te [file] - text editor",
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