#include "measure_battery.h"
#include "stm8l.h"

uint8_t measure_battery() {
    uint16_t sum = 0;
    uint8_t battery_voltage;
    
    CLK_PCKENR2 |= CLK_PCKENR2_ADC1;
    ADC1_TRIGR1 = ADC_TRIGR1_VREFINTON;
    ADC1_CR1 = (ADC_CR1_ADON | (0b0 * ADC_CR1_RES0));
    ADC1_SQR1 = ADC_SQR1_DMAOFF | ADC_SQR1_CHSEL_SVREFINT;
    ADC1_SR = 0;

    sum = 0;
    for (uint8_t i = 0; i < 2; i++) {
        ADC1_CR1 |= ADC_CR1_START; // start conversion
        while (!(ADC1_SR & ADC_SR_EOC))
            ;
        sum += ((uint16_t)ADC1_DRH << 8) | ADC1_DRL;
	}
	ADC1_TRIGR1 = 0; // disable Vrefint
	ADC1_CR1 = 0; // disable ad
	CLK_PCKENR2 &= ~CLK_PCKENR2_ADC1;
	sum >>= 1;
	battery_voltage = (50135 + (sum >> 1)) / sum;
	
    return battery_voltage;
}
