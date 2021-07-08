#include "button_isr.h"
#include "clear_singleshot_timer.h"
#include "set_singleshot_timer.h"
#include "stm8l.h"
#include "medion-hm-sec-sc.h"

extern volatile uint8_t timer_request;
extern volatile e_request request_operation;
volatile e_button_press_type button_operation = BUTTON_PRESS_NONE;

void handle_button_pressed() {
    button_operation = BUTTON_PRESS_NONE;
    clear_singleshot_timer();
    set_singleshot_timer(50);
    timer_request |= TIMER_BUTTON;
}

void handle_button_released() {
    switch(button_operation) {
    case BUTTON_PRESS_SHORT:
        request_operation = OPERATION_BUTTON_SHORT;
        break;
    case BUTTON_PRESS_LONG:
        request_operation = OPERATION_BUTTON_LONG;
        break;
    case BUTTON_PRESS_NONE:

        break;
    }
    clear_singleshot_timer();
    timer_request &= ~TIMER_BUTTON;
    button_operation = BUTTON_PRESS_NONE;
}

void button_isr() __interrupt(13) {
    EXTI_SR1 |= BUTTON;
    if(PA_IDR & BUTTON) {
        // Button released
        handle_button_released();
    } else {
        // Button pressed
        handle_button_pressed();
    }
}
