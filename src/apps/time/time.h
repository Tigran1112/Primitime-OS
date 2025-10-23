#ifndef TIME_H
#define TIME_H

#include <stdint.h>

void init_rtc();
uint8_t get_time(int phase);

#endif