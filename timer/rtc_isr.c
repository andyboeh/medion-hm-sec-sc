#include "rtc_isr.h"
#include "stm8l.h"
#include "medion-hm-sec-sc.h"

extern volatile e_request request_operation;

void rtc_isr(void) __interrupt(4) {
    RTC_ISR2 &= ~(RTC_ISR2_WUTF);
    request_operation = OPERATION_MEASURE_BATTERY;
}
