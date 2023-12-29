#include "tick_deinit.h"
#include "clear_timeout.h"
#include "stm8l.h"

#include <stdbool.h>

extern volatile bool tick_ok;

void tick_deinit(void)
{
	clear_timeout();
    TIM2_SR1 &= ~(1<<0); // Clear interrupt
	CLK_PCKENR1 &= ~CLK_PCKENR1_TIM2;
    tick_ok = false;
}
