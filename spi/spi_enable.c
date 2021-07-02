#include "spi_enable.h"
#include "stm8l.h"

void spi_enable()
{
	CLK_PCKENR1 |= CLK_PCKENR1_SPI;
	SPI1_CR1 |= SPI_CR1_SPE; // enable spi
}
