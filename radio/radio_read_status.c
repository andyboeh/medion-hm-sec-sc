#include "radio_read_status.h"
#include "radio_read_reg.h"
#include "radio_read_int.h"
#include "si4430.h"

uint8_t radio_read_status(void)
{
	if (!radio_read_int()) {
		uint8_t status1 = radio_read_reg(SI4430_STATUS1);
		uint8_t status2 = radio_read_reg(SI4430_STATUS2);
#ifdef DEBUG_STATI
		stati[stati_in].status1 = status1;
		stati[stati_in].status2 = status2;
		if (++stati_in == sizeof(stati) / sizeof(status_t))
			stati_in = 0;
#ifdef LCD_INCLUDED
		lcd_data.value = stati_in & 0xf;
#endif
#endif
		return status1;
	}
	return 0;
}
