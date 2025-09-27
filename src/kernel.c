#include "input/keyboard/keyboard.h"
#include "interprer/interprer.h"
#include "screen/screen.h"
#include <stdbool.h>

void kmain(void) 
{
    clear();
    print("OS Started - CLI mode. Write help for commands", 0, 0x0a);
    
    int str = 24;
    int str_handler = str;
    bool set_zero = false;
    while (1) 
    {
        if (command_mode) 
        {
            replace("Primitive OS>", 23, 0x0a);
            str = str_handler;
        }
        else
        {
            if (!set_zero)
            {
                str = 0;
                set_zero = true;
            }
            
        }
        char c = scan2char(read_keyboard());
        if (c == '~')
        {
            if (command_mode)
            {
                char *cmd = get_str(str);
                clear_str(str);
                exec(cmd);
            }
            else
            {
                str++;
            }
        }
        else if (c == '`')
        {
            backspace(str);
        }
        else if (c == 'L')
        {
            command_mode = false;
            set_zero = false;
        }
        else if (c != 0x00)
        {
            print_char(c, str, 0x0a);
        }
    }
}