#include "led_off.h"
#include "stm8l.h"
#include "medion-hm-sec-sc.h"

void led_off(void) {
    PA_ODR &= ~LED;
}
