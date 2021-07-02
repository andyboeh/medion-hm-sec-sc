#include "radio_read_burst.h"
#include "spi_send_byte.h"
#include "spi_defines.h"
#include "si4430.h"

void radio_read_burst(uint8_t addr, uint8_t len, uint8_t * data)
{
	radio_select();
	spi_send_byte(addr | READ_BURST);
	for ( ; len; len--)
		*(data++) = spi_send_byte(0x0);
	radio_deselect();
}
