#include "as_config_write.h"
#include "stm8l.h"
#include "as_config_data.h"
#include "as_defines.h"

extern config_data cdata;

bool as_config_write(uint8_t channel, uint8_t length, uint8_t * data)
{
    if (!cdata.active || cdata.channel != channel)
		return false;

	// enable eeprom programming
	FLASH_DUKR = 0xAE;
	FLASH_DUKR = 0x56;
	while (!(FLASH_IAPSR & FLASH_IAPSR_DUL))
		;

	for (uint8_t i = 0; i + 1 < length; i += 2) {
        if (cdata.channel == 0 && cdata.list == 0) {
			if (data[i] == 0x0a)
				((uint8_t*)hm_master_id)[0] = data[i + 1];
			else if (data[i] == 0x0b)
				((uint8_t*)hm_master_id)[1] = data[i + 1];
			else if (data[i] == 0x0c)
				((uint8_t*)hm_master_id)[2] = data[i + 1];
			else if (data[i] == 0x0d)
				*min_battery_voltage = data[i + 1];
			else
				continue; // don't wait for write completion
		} else
			continue; // don't wait for write completion

		// wait for eeprom write completion
		while (!(FLASH_IAPSR & FLASH_IAPSR_EOP))
			;
	}

	FLASH_IAPSR &= ~FLASH_IAPSR_DUL;

	return true;
}
