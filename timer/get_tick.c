#include "get_tick.h"
#include "stm8l.h"

extern volatile uint16_t tick_count;

uint16_t get_tick()
{
    return tick_count;
}
