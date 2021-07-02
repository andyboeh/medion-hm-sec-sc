#include "radio_enter_receive.h"
#include "si4430.h"
#include "radio_write_reg.h"
#include "radio_defines.h"

extern e_radio_state radio_state;

void radio_enter_receive(uint8_t max_length)
{
	radio_write_reg(SI4430_OMFC2, SI4430_FFCLRRX | SI4430_FFCLRTX); // clear fifos
	radio_write_reg(SI4430_OMFC2, 0);
	radio_write_reg(SI4430_PKLEN, max_length + 3);
	radio_write_reg(SI4430_OMFC1, SI4430_RXON); // enter receive mode
	radio_state = radio_receiving;
}
