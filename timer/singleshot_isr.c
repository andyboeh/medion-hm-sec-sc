#include "singleshot_isr.h"
#include "clear_singleshot_timer.h"
#include "stm8l.h"
#include "medion-hm-sec-sc.h"

extern volatile e_request request_operation;
extern volatile uint8_t timer_request;

void singleshot_isr() __interrupt(21) {
    TIM3_SR1 &= ~(1 << 0); // Clear interrupt
    if(timer_request & TIMER_BUTTON) {
        request_operation = OPERATION_CONFIG_PAIR;
    }
    if(timer_request & TIMER_REL) {
        request_operation = OPERATION_CHECK_REL;
    }
    timer_request = TIMER_NONE;
    clear_singleshot_timer();
}
