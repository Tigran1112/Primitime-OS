#include "input/keyboard.c"
#include "shell/interprer.c"

void kmain(void) 
{
    clear();
    print("OS Started - CLI mode. Write help for commands", 0, 0x0a);
    
    int str = 24;
    int str_handler = str;
    while (1) 
    {
        if (command_mode) 
        {
            replace("Primitive OS>", 23, 0x0a);
            str = str_handler;
        }
        else str = 0;
        char c = scan2char(read_keyboard());
        if (c == '~')
        {
            if (command_mode)
            {
                char *cmd = get_str(str);
                clear_str(str);
                exec(cmd);
            }
        }
        else if (c == '`')
        {
            backspace(str);
        }
        else if (c == 'L')
        {
            command_mode = false;
        }
        else if (c != 0x00)
        {
            print_char(c, str, 0x0a);
        }
    }
}