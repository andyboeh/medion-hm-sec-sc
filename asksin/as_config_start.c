#include "as_config_start.h"
#include "as_config_data.h"

config_data cdata = { .active = false };

bool as_config_start(uint8_t channel, uint8_t list)
{
    cdata.channel = channel;
    cdata.list = list;
    cdata.active = true;

	return true;
}
