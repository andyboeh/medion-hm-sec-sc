#include "get_tick.h"
#include "stm8l.h"

extern volatile uint16_t tick_count;

uint16_t get_tick(void)
{
    return tick_count;
}
