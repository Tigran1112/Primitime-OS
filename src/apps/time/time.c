#include <stdint.h>
#include "interprer/ports/ports.h"

#define rtc_index 0x70
#define rtc_data 0x71

#define seconds 0x00
#define minutes 0x02
#define hours 0x04

void init_rtc()
{
    outb(0x0B, rtc_index);
    uint8_t reg_b = inb(rtc_data);
    reg_b |= 0x02;
    reg_b |= 0x40;
    outb(0x0B, rtc_index);
    outb(reg_b, rtc_data);
}

int read_rtc(uint8_t index)
{
    outb(index, rtc_index);
    return inb(rtc_data);
}
uint8_t bcd_to_bin(uint8_t bcd) { return (bcd >> 4) * 10 + (bcd & 0x0F); }

int get_time(int phase)
{
    if (phase == 0)
    {
        return bcd_to_bin(read_rtc(seconds) & 0x7F);
    }
    else if (phase == 1)
    {
        return bcd_to_bin(read_rtc(minutes) & 0x7F);
    }
    else if (phase == 2)
    {
        return bcd_to_bin(read_rtc(hours) & 0x3F);
    }
}