#include "tick_deinit.h"
#include "clear_timeout.h"
#include "stm8l.h"

void tick_deinit()
{
	clear_timeout();
	CLK_PCKENR1 &= ~CLK_PCKENR1_TIM2;
}
