#include "as_config_end.h"
#include "as_config_data.h"

extern config_data cdata;

bool as_config_end(uint8_t channel)
{
    bool ack = cdata.active && cdata.channel == channel;
    cdata.active = false;

	return ack;
}
