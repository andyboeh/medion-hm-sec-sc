#include "led_timer_deinit.h"
#include "stm8l.h"

void led_timer_deinit() {
    CLK_PCKENR1 &= ~CLK_PCKENR1_TIM4; // enable clock
}
