#include "radio_write_reg.h"
#include "spi_defines.h"
#include "spi_send_byte.h"
#include "si4430.h"

void radio_write_reg(uint8_t addr, uint8_t data)
{
	radio_select();
	spi_send_byte(addr | WRITE_BURST);
	spi_send_byte(data);
	radio_deselect();
}
