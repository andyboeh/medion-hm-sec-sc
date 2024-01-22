#include "rtc_battery_timer_enable.h"
#include "stm8l.h"
#include "led_on.h"

void rtc_battery_timer_enable(void) {
    while(CLK_CRTCR & CLK_CRTCR_RTCSWBSY);
    CLK_CRTCR = 0x04; // Enable LSI clock, RTCDIV = 0

    while(!(CLK_ICKCR & CLK_ICKCR_LSIRDY));
    CLK_PCKENR2 |= CLK_PCKENR2_RTC;

    RTC_WPR = 0xCA;
    RTC_WPR = 0x53;

    RTC_ISR1 |= RTC_ISR1_INIT;
    while(!(RTC_ISR1 & RTC_ISR1_INITF));

    RTC_SPRERH = 0x01; // 303 = 0x12f
    RTC_SPRERL = 0x2F; // 303 = 0x12f
    RTC_APRER = 0x7c;  // 124 = 0x7c

    // Enable write access to the WUCKSEL register
    RTC_CR2 &= ~(RTC_CR2_WUTE);
    while(!(RTC_ISR1 & RTC_ISR1_WUTWF));

    //RTC_CR1 |= 0x06; // Select 1Hz clock and add 2^16 to the value
    RTC_CR1 |= 0x04; // Select 1Hz clock

    RTC_WUTRH = 0x51;
    RTC_WUTRL = 0x80; // 24h timeout

    //RTC_ISR1 &= ~(RTC_ISR1_WUTWF); // Clear write access
    RTC_CR2 |= RTC_CR2_WUTIE; // Enable Wake up timer interrupt
    RTC_CR2 |= RTC_CR2_WUTE; // Enable Wake up timer
    while(!(RTC_ISR1 & RTC_ISR1_WUTWF));

    RTC_ISR1 &= ~(RTC_ISR1_INIT);
    RTC_WPR = 0xFF; // Lock RTC
}
