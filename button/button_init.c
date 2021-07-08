#include "button_init.h"
#include "stm8l.h"
#include "medion-hm-sec-sc.h"
#include "button_isr.h"
#include <stdbool.h>

extern bool button_pressed_while_boot;

void button_init() {
    PA_DDR &= ~BUTTON;
    PA_CR1 |= BUTTON;
    PA_CR2 |= BUTTON;
    EXTI_CR2 |= (1 << 3) | (1 << 2); // Either edge interrupt
    if(!(PA_IDR & BUTTON)) {
        handle_button_pressed();
        button_pressed_while_boot = true;
    }
}
