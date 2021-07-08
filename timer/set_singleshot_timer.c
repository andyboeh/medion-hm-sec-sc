#include "set_singleshot_timer.h"
#include "stm8l.h"

void set_singleshot_timer(uint16_t timeout_ms) {
    uint16_t reload_value = timeout_ms * 62;

    CLK_PCKENR1 |= CLK_PCKENR1_TIM3; // enable clock
    TIM3_PSCR = 5; // prescale by 32
    TIM3_EGR = 1; // force update to make all changes take effect immediately

    TIM3_CNTRH = reload_value >> 8;
    TIM3_CNTRL = reload_value & 0xff;

    TIM3_ARRH = reload_value >> 8;
    TIM3_ARRL = reload_value & 0xff;

    TIM3_IER = 1; // Enable interrupt
    TIM3_SR1 = 1; // Clear update interrupt flag

    TIM3_CR1 |= 1 << 7; // Auto-reload enable
    TIM3_CR1 |= 1 << 4; // Count down
    TIM3_CR1 |= TIMx_CR1_CEN; // Enable counter

    TIM3_SR1 &= ~(1 << 0); // Clear interrupt

    //WFE_CR1 |= WFE_CR1_TIM2_EV1; // timer 2 capture and compare events
    //WFE_CR1 |= WFE_CR1_TIM2_EV0;
}
