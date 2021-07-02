#include "tick_isr.h"
#include "stm8l.h"
#include <stdint.h>
#include <stdbool.h>

extern volatile uint16_t tick_count;
extern volatile uint16_t timeout_at;
extern volatile bool wait_for_timeout;

void tick_isr() __interrupt(19) {
    TIM2_SR1 &= ~(1<<0); // Clear interrupt
    tick_count++;
    if(wait_for_timeout) {
        if(tick_count == timeout_at) {
            wait_for_timeout = false;
        }
    }
}
