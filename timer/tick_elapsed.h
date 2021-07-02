#ifndef TICK_ELAPSED_H
#define TICK_ELAPSED_H

#include "get_tick.h"

#define GET_MACRO(_1,_2,NAME,...) NAME
#define tick_elapsed(...) GET_MACRO(__VA_ARGS__, tick_elapsed2, tick_elapsed1)(__VA_ARGS__)
		
#define tick_elapsed1(tick) (!((get_tick() - (tick)) & ((uint16_t)1<<15)))
#define tick_elapsed2(now, tick) (!(((now) - (tick)) & ((uint16_t)1<<15)))

#endif //TICK_ELAPSED_H
