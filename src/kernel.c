#include "input/keyboard/keyboard.h"
#include "interprer/interprer.h"
#include "screen/screen.h"
#include "apps/time/time.h"

int str = 24;

void post_loading()
{
    init_rtc();
    clear();
    print("OS Started. Write help for commands", 0, 0x0a);
    
    
    int str = 24;
    int str_handler = str;

    while (1) 
    {
        replace("Primitive OS>", str - 1, 0x0a);
        str = str_handler;
        char c = scan2char(read_keyboard());
        if (c == '~')
        {
            char *cmd = get_str(str);
            clear_str(str);
            exec(cmd);
        }
        else if (c == '`')
        {
            hide_cursor();
            backspace(str);
            show_cursor();
        }
        else if (c != 0x00) 
        {
            hide_cursor();
            print_char(c, str, 0x0a);
            show_cursor();
        }
    }
}