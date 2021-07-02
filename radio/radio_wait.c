#include "radio_wait.h"
#include "radio_defines.h"
#include "radio_sent.h"
#include "radio_received.h"
#include "radio_wait_int.h"
#include "radio_write_reg.h"
#include "si4430.h"

extern e_radio_state radio_state;

// wait for either packet reception or packet sent ... but for at most until timeout_at
// returns true if operation was successfull, false on timeout
bool radio_wait(uint16_t timeout_at)
{
	while (true) {
		if (!radio_wait_int(timeout_at)) {
			radio_write_reg(SI4430_OMFC1, 0); // goto idle mode
			return false;
		}
		if (radio_state == radio_sending) {
			if (radio_sent())
				return true;
		} else if (radio_received())
			return true;
	}
}
