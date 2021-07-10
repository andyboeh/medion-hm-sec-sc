#include "rtc_battery_timer_enable.h"
#include "stm8l.h"

void rtc_battery_timer_enable() {
    RTC_WPR = 0xCA;
    RTC_WPR = 0x53;

    while(CLK_CRTCR & CLK_CRTCR_RTCSWBSY);
    CLK_CRTCR &= ~(0x30); // Disable RTC Clock
    CLK_CRTCR |= (1 << 2); // Enable LSI Clock for RTC (RTCSEL)
    // RTCDIV
}
