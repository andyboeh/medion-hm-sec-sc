#include "as_poll.h"
#include "as_send_device_info.h"
#include "as_listen.h"
#include "spi_disable.h"
#include "spi_enable.h"
#include "led_blink.h"
#include <stdbool.h>
#include "as_defines.h"

extern bool finished;
bool as_ok;

void as_poll()
{
	spi_enable();
	finished = false;
	as_ok = false;

    if(ID_IS_NULL(hm_master_id)) {
        led_blink(LED_BLINK_FAST);
    } else {
        led_blink(LED_BLINK_SLOW);
    }

    as_send_device_info();
    /*
    if (ID_IS_NULL(hm_master_id)) {
        led_blink(LED_BLINK_FAST);
		as_send_device_info();
    }
    else {
        led_blink(LED_BLINK_SLOW);
		as_send_status();
   }
   */
	
	as_listen();

    if(as_ok) {
        led_blink(LED_BLINK_ONCE);
    } else {
        led_blink(LED_BLINK_THRICE);
    }

	spi_disable();
}
