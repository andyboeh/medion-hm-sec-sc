#include "led_off.h"
#include "stm8l.h"
#include "medion-hm-sec-sc.h"

void led_off() {
    PA_ODR &= ~LED;
}
