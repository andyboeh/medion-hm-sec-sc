#include "spi_init.h"
#include "stm8l.h"
#include "medion-hm-sec-sc.h"
#include "spi_defines.h"

void spi_init()
{
	PB_ODR &= ~SCLK;
	PB_CR1 = nSEL | SCLK | MOSI; // push-pull
	PB_DDR = nSEL | SCLK | MOSI; // output
    radio_deselect();

	CLK_PCKENR1 |= CLK_PCKENR1_SPI;
	SPI1_CR2 = SPI_CR2_SSM | SPI_CR2_SSI; // software slave management: master
	SPI1_CR1 = 0b0*SPI_CR1_BR | SPI_CR1_MSTR; // f_sysclk / 2, master
}
