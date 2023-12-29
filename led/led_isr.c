#include "led_isr.h"
#include "led_blink.h"
#include "led_toggle.h"
#include "led_on.h"
#include "led_off.h"
#include "stm8l.h"
#include <stdint.h>

extern volatile e_blink_type led_blink_type;
volatile uint8_t led_blink_count = 0;
volatile uint8_t isr_run_count = 0;

void led_isr(void) __interrupt(25) {
    TIM4_SR1 &= ~(1 << 0); // Clear interrupt
    switch(led_blink_type) {
    case LED_BLINK_ONCE:
        if(isr_run_count % 5 != 0)
            break;
        if(led_blink_count == 0) {
            led_on();
            led_blink_count++;
        } else {
            led_off();
            led_blink(LED_BLINK_OFF);
        }
    break;
    case LED_BLINK_THRICE:
        if(isr_run_count % 5 != 0)
            break;
        if(led_blink_count % 2 == 0) {
            led_on();
        } else {
            led_off();
        }
        led_blink_count++;
        if(led_blink_count == 6)
            led_blink(LED_BLINK_OFF);
    break;
    case LED_BLINK_FAST:
        if(isr_run_count % 2 != 0)
            break;
        led_toggle();
    break;
    case LED_BLINK_SLOW:
        if(isr_run_count % 5 != 0)
            break;
        led_toggle();
    break;
    }
    isr_run_count++;
}
