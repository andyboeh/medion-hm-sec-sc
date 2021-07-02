#include "radio_deinit.h"
#include "stm8l.h"

void radio_deinit()
{
	PB_CR2 &= ~(1u<<4); // PB4 external interrupt enabled
	WFE_CR2 &= ~WFE_CR2_EXTI_EV4; // nIRQ is PB4 which is by default mapped to EXTI4
}

