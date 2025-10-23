#include "interprer/ports/ports.h"
#include <stdint.h>

#define pit_cho 0x40
#define pit_cmd 0x43
#define pit_freq 1193180

void init_timer(uint32_t freq)
{
    uint32_t div = pit_freq / freq;
    outb(pit_cmd, 0x36);
    outb(pit_cho, div & 0xff);
    outb(pit_cho, (div >> 8) & 0xff);
}