#include "screen/screen.h"

int car_pos = 5;

void init_racer()
{
    clear();
    replace(" #### ", 5, car_pos, 0x04);
    replace("######", 6, car_pos, 0x08);
    replace(" #### ", 7, car_pos, 0x04);
    replace("######", 8, car_pos, 0x08);
    replace(" #### ", 9, car_pos, 0x04);
}