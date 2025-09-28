#include <stdbool.h>
#include "screen/screen.h"

int indent = 35;
bool racer_running = false;
void update_racer()
{
    clear();
    replace("Game running", 0, 0x0a);
    for (int i = 0; i < indent; i++)
    {
        print_char(' ', 14, 0x0a);
        print_char(' ', 15, 0x0a);
        print_char(' ', 16, 0x0a);
        print_char(' ', 17, 0x0a);
        print_char(' ', 18, 0x0a);
    }
    print(" ### ", 14, 0x0c);
    print("#####", 15, 0x08);
    print(" ### ", 16, 0x0c);
    print("#####", 17, 0x08);
    print(" ### ", 18, 0x0c);
}
void init_racer()
{
    racer_running = true;
    update_racer();
}
void racer_move_left()
{
    indent = 20;
    update_racer();
}
void racer_move_right()
{
    indent = 55;
    update_racer();
}
void racer_move_forward()
{
    indent = 35;
    update_racer();
}
void stop_racer()
{
    racer_running = false;
    clear();
}