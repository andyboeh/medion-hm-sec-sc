#include "radio_received.h"
#include "radio_defines.h"
#include "si4430.h"
#include "radio_read_status.h"

extern e_radio_state radio_state;

bool radio_received()
{
	if (radio_state != radio_receiving)
		return false;
	if (radio_read_status() & SI4430_PKGVALID) {
		radio_state = radio_idle;
		return true;
	}
	return false;
}