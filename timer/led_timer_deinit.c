#include "led_timer_deinit.h"
#include "stm8l.h"

void led_timer_deinit(void) {
    TIM4_SR1 &= ~(1 << 0); // Clear interrupt
    CLK_PCKENR1 &= ~CLK_PCKENR1_TIM4; // enable clock
}
