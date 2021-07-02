#include "radio_wait_int.h"
#include "tick_elapsed.h"
#include "radio_read_int.h"
#include "set_timeout.h"
#include "clear_timeout.h"
#include "stm8l.h"

extern volatile bool wait_for_timeout;

// TODO move this to RAM to further reduce current consumption
bool radio_wait_int(uint16_t timeout)
{
    set_timeout(timeout);
    while (wait_for_timeout && radio_read_int()) { // -1 for safety: i don't know if set_timeout() timesout if timeout_at is already reached!
        EXTI_SR1 = EXTI_SR1_P4F; // reset external interrupt port 4

        wfi();
	}

    clear_timeout();
	//clear_timeout(); // i think we don't need this? TODO when leaving e.g. the bootloader this should be reset
	// TODO we don't have to reset anything else as long as the WFE flags stay enabled. they will prevent any real interrupt

	return !radio_read_int();
}
