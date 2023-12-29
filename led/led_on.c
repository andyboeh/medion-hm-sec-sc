#include "led_on.h"
#include "stm8l.h"
#include "medion-hm-sec-sc.h"

void led_on(void) {
    PA_ODR |= LED;
}
