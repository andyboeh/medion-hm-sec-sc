#include "radio_read_reg.h"
#include "spi_defines.h"
#include "spi_send_byte.h"
#include "si4430.h"

uint8_t radio_read_reg(uint8_t addr)
{
	uint8_t val;

	radio_select();
	//wait_miso(); // only cc1101
	spi_send_byte(addr | READ_BURST);
	val = spi_send_byte(0x0);
	radio_deselect();

	return val;
}
