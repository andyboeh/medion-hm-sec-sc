#include "led_init.h"
#include "stm8l.h"
#include "medion-hm-sec-sc.h"

void led_init() {
    PA_CR1 = LED;
    PA_DDR = LED;
}
