#include "relay_isr.h"
//#include "clear_singleshot_timer.h"
//#include "set_singleshot_timer.h"
#include "stm8l.h"
#include "medion-hm-sec-sc.h"

//extern volatile uint8_t timer_request;
extern volatile e_request request_operation;

void relay_isr() __interrupt(14) {
    EXTI_SR1 |= REL; // clear interrupt
    request_operation = OPERATION_CHECK_REL;
    // We don't need the debounce timer, since there is an
    // RC filter present!

    //clear_singleshot_timer();
    //set_singleshot_timer(100);
    //timer_request |= TIMER_REL;

}
