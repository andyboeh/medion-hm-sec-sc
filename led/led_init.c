#include "led_init.h"
#include "stm8l.h"
#include "medion-hm-sec-sc.h"

void led_init(void) {
    PA_CR1 = (LED & 0xff);
    PA_DDR = (LED & 0xff);
}
