#include "rtc_battery_timer_disable.h"
#include "stm8l.h"

void rtc_battery_timer_disable(void) {
    RTC_WPR = 0xCA;
    RTC_WPR = 0x53;

    while(CLK_CRTCR & CLK_CRTCR_RTCSWBSY);
    CLK_CRTCR = 0x00; // Disable RTC Clock
    CLK_PCKENR2 &= ~(CLK_PCKENR2_RTC);
}
