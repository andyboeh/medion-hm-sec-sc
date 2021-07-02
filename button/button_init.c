#include "button_init.h"
#include "stm8l.h"
#include "medion-hm-sec-sc.h"

void button_init() {
    PA_DDR &= ~BUTTON;
    PA_CR1 |= BUTTON;
    PA_CR2 |= BUTTON;
    EXTI_CR2 |= (1 << 3); // | (1 << 2); // Falling edge interrupt
}
