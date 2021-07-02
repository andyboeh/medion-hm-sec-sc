#include "spi_send_byte.h"
#include "stm8l.h"

uint8_t spi_send_byte(uint8_t data)
{
	//while (!(SPI1_SR & SPI_SR_TXE) || (SPI1_SR & SPI_SR_RXNE) || (SPI1_SR & SPI_SR_BSY))
	//	(void)SPI1_DR;
	SPI1_DR = data;
	while (!(SPI1_SR & SPI_SR_RXNE))
		;
	return SPI1_DR;
}
