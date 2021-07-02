#include "spi_disable.h"
#include "stm8l.h"

void spi_disable()
{
	while (!(SPI1_SR & SPI_SR_TXE) || (SPI1_SR & SPI_SR_BSY))
		;
	SPI1_CR1 &= ~SPI_CR1_SPE;
	CLK_PCKENR1 &= ~CLK_PCKENR1_SPI;
}

