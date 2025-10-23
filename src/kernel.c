#include "input/keyboard/keyboard.h"
#include "interprer/interprer.h"
#include "screen/screen.h"
#include "apps/time/time.h"

int old_time = 0;
int str = 24;
volatile int tick = 0;

void post_loading()
{
    init_rtc();
    clear();
    print("OS Started. Write help for commands", 0, 0x0a);
}
void keyboard()
{
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
void kmain(void) 
{
    post_loading();
    while (1) 
    {
        replace("Primitive OS>", str - 1, 0x0a);
        keyboard();
        tree_update();
    }
}