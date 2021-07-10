#include "relay_init.h"
#include "stm8l.h"
#include "medion-hm-sec-sc.h"

void relay_init() {
    PA_DDR &= ~REL; // Configure input
    //PA_CR1 |= REL; // Enable pull-up
    PA_CR1 &= ~REL; // Disable pull-up, there is an external circuit present
    PA_CR2 |= REL; // Enable external interrupt
    EXTI_CR2 |= (1 << 4) | (1 << 5); // Enable rising and falling edge interrupt
}
