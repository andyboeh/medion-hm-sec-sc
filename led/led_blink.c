#include "led_blink.h"
#include "led_timer_init.h"
#include "led_timer_deinit.h"
#include <stdint.h>

volatile e_blink_type led_blink_type;
extern volatile uint8_t led_blink_count;

void led_blink(e_blink_type type) {
    led_blink_count = 0;
    switch(type) {
    case LED_BLINK_OFF:
        led_timer_deinit();
        led_blink_type = type;
    break;
    case LED_BLINK_ONCE:
    case LED_BLINK_THRICE:
    case LED_BLINK_FAST:
    case LED_BLINK_SLOW:
        led_timer_init();
        led_blink_type = type;
    break;
    }
}
