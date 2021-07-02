#include "button_isr.h"
#include "clear_singleshot_timer.h"
#include "set_singleshot_timer.h"
#include "stm8l.h"
#include "medion-hm-sec-sc.h"

extern volatile uint8_t timer_request;

void button_isr() __interrupt(13) {
    EXTI_SR1 |= BUTTON;
    clear_singleshot_timer();
    set_singleshot_timer(20);
    timer_request |= TIMER_BUTTON;
}
