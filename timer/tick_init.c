#include "tick_init.h"
#include "stm8l.h"
#include <stdbool.h>

//const uint16_t reload_value = 62500; // 1 second
const uint16_t reload_value = 62; // 1 ms

volatile uint16_t tick_count = 0;
volatile bool wait_for_timeout = false;
volatile uint16_t timeout_at = 0;

volatile bool tick_ok = false;

void tick_init()
{
    if(tick_ok)
        return;

	// enable tick counter
    CLK_PCKENR1 |= CLK_PCKENR1_TIM2; // enable clock
    TIM2_PSCR = 5; // prescale by 32
    TIM2_EGR = 1; // force update to make all changes take effect immediately

    TIM2_CNTRH = reload_value >> 8;
    TIM2_CNTRL = reload_value & 0xff;

    TIM2_ARRH = reload_value >> 8;
    TIM2_ARRL = reload_value & 0xff;

    TIM2_IER = 1; // Enable interrupt
    TIM2_SR1 = 1; // Clear update interrupt flag

    TIM2_CR1 |= 1 << 7; // Auto-reload enable
    TIM2_CR1 |= 1 << 4; // Count down
    TIM2_CR1 |= TIMx_CR1_CEN; // Enable counter

    //WFE_CR1 |= WFE_CR1_TIM2_EV1; // timer 2 capture and compare events
    //WFE_CR1 |= WFE_CR1_TIM2_EV0;
    tick_ok = true;
}
