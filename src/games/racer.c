#include <stdbool.h>
#include "base/base.h"
#include "screen/screen.h"

bool racer_running = false;

int indent = 35;
int indent_conus = 0;

int tree_direction = 0;
int tree_pos = 0;

void update_tree()
{
    if (tree_pos >= 24)
    {
        clear_str(tree_pos);
        clear_str(tree_pos + 1); 
        clear_str(tree_pos + 2);
        tree_pos = 0;
        return;
    }
    
    clear_str(tree_pos - 1);
    clear_str(tree_pos);
    clear_str(tree_pos + 1);
    
    print("  #####", tree_pos, 0x02);
    print("#######", tree_pos + 1, 0x06);
    print("  #####", tree_pos + 2, 0x02);
    
    tree_pos++;

    update_tree();
}
void update_tree()
{
    if (tree_pos >= 24)
    {
        clear_str(tree_pos);
        clear_str(tree_pos + 1); 
        clear_str(tree_pos + 2);
        tree_pos = 0;
        return;
    }
    
    clear_str(tree_pos - 1);
    clear_str(tree_pos);
    clear_str(tree_pos + 1);
    
    print("  #####", tree_pos, 0x02);
    print("#######", tree_pos + 1, 0x06);
    print("  #####", tree_pos + 2, 0x02);
    
    tree_pos++;
}

void spawn_tree()
{
    if (rand() % 100 <= 25)
    {
        tree_direction = rand() % 3;
        switch (tree_direction)
        {
            case 0: indent_conus = 20; break;
            case 1: indent_conus = 35; break;
            case 2: indent_conus = 55; break;
        }
    }
}
void init_racer()
{
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
    clear();
}
void game_tick()
{
    static int tree_timer = 0;
    tree_timer++;
    if (tree_timer >= 10)
    {
        update_tree();
        tree_timer = 0;
    }
    
    if (rand() % 100 <= 5)
    {
        spawn_tree();
    }
}