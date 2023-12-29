#include "led_toggle.h"
#include "stm8l.h"
#include "medion-hm-sec-sc.h"

void led_toggle(void) {
    PA_ODR ^= LED;
}
