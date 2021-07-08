#include "singleshot_isr.h"
#include "set_singleshot_timer.h"
#include "clear_singleshot_timer.h"
#include "stm8l.h"
#include "medion-hm-sec-sc.h"
#include "led_blink.h"
#include "led_toggle.h"

extern volatile e_request request_operation;
extern volatile uint8_t timer_request;
extern volatile e_button_press_type button_operation;

void singleshot_isr() __interrupt(21) {
    TIM3_SR1 &= ~(1 << 0); // Clear interrupt
    if(timer_request & TIMER_BUTTON) {
        switch(button_operation) {
        case BUTTON_PRESS_NONE:
            button_operation = BUTTON_PRESS_SHORT;
            clear_singleshot_timer();
            set_singleshot_timer(1000);
            return;
        case BUTTON_PRESS_SHORT:
            button_operation = BUTTON_PRESS_LONG;
            break;
        }
    }
    if(timer_request & TIMER_REL) {
        request_operation = OPERATION_CHECK_REL;
    }
    timer_request = TIMER_NONE;
    clear_singleshot_timer();
}
