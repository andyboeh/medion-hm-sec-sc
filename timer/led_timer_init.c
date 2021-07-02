#include "led_timer_init.h"
#include "stm8l.h"

void led_timer_init() {
    CLK_PCKENR1 |= CLK_PCKENR1_TIM4; // enable clock
    // enable clock
    TIM4_EGR = 1;

    TIM4_CNTR = 6; //reset to ARR value
    TIM4_PSCR = 0b1111; // Prescaler 32768 -> 1 tick = 16ms
    TIM4_ARR = 6; // Roughly 100ms

    TIM4_SR1 = 1; // Clear update interrupt flag
    TIM4_IER = 1; // enable interrupt
    TIM4_CR1 |= 1; // Enable timer
}
