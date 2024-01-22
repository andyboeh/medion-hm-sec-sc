#include "rtc_battery_timer_disable.h"
#include "stm8l.h"

void rtc_battery_timer_disable(void) {
    RTC_WPR = 0xCA;
    RTC_WPR = 0x53;

    RTC_ISR2 &= ~(RTC_ISR2_WUTF); // Clear interrupt
    RTC_CR2 &= ~RTC_CR2_WUTIE; // Disable Wake up timer interrupt
    RTC_CR2 &= ~RTC_CR2_WUTE; // Disable Wake up timer
    while(!(RTC_ISR1 & RTC_ISR1_WUTWF));

    while(CLK_CRTCR & CLK_CRTCR_RTCSWBSY);
    CLK_CRTCR = 0x00; // Disable RTC Clock
    CLK_PCKENR2 &= ~(CLK_PCKENR2_RTC);

    RTC_WPR = 0xFF; // Lock RTC
}
