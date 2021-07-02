#ifndef LED_BLINK_H
#define LED_BLINK_H

typedef enum {
    LED_BLINK_OFF = 0,
    LED_BLINK_ONCE,
    LED_BLINK_THRICE,
    LED_BLINK_FAST,
    LED_BLINK_SLOW
} e_blink_type;

void led_blink(e_blink_type type);

#endif //LED_BLINK_H
