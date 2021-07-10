#include "wait_for_led.h"
#include "led_blink.h"
#include "stm8l.h"

extern volatile e_blink_type led_blink_type;

void wait_for_led() {
    while(led_blink_type != LED_BLINK_OFF)
        wfi();
}
