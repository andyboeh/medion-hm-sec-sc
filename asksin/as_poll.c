#include "as_poll.h"
#include "as_send_device_info.h"
#include "as_send_status.h"
#include "as_listen.h"
#include "spi_disable.h"
#include "spi_enable.h"
#include <stdbool.h>
#include "as_defines.h"

static bool finished;
bool as_ok;

void as_poll()
{
	spi_enable();
	finished = false;
	as_ok = false;

	if (ID_IS_NULL(hm_master_id))
		as_send_device_info();
	else
		as_send_status();
	
	as_listen();
	spi_disable();
}
