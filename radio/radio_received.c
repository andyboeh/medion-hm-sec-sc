#include "radio_received.h"
#include "radio_defines.h"
#include "radio_write_reg.h"
#include "si4430.h"
#include "radio_read_status.h"

extern e_radio_state radio_state;

bool radio_received(void)
{
	if (radio_state != radio_receiving)
		return false;
	if (radio_read_status() & SI4430_PKGVALID) {
        radio_write_reg(SI4430_OMFC1, 0); // goto idle mode
		radio_state = radio_idle;
		return true;
	}
	return false;
}
