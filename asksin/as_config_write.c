#include "as_config_write.h"
#include "stm8l.h"
#include "as_config_data.h"
#include "as_defines.h"
#include "as_handle_cyclic_info.h"

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

        switch(data[i]) {
        case 0x08: // AES_ENABLED
            if(cdata.channel == 1 && cdata.list == 1) {
                ((uint8_t*)aes_channel1)[0] = data[i + 1];
            } else {
                continue;
            }
            break;
        case 0x09: // CYCLIC_INFO_MSG
            if(cdata.channel == 0 && cdata.list == 0) {
                ((uint8_t*)cyclic_info)[0] = data[i + 1];
                as_handle_cyclic_info();
            } else {
                continue;
            }
            break;
        case 0x0a:
            if(cdata.channel == 0 && cdata.list == 0) {
                ((uint8_t*)hm_master_id)[0] = data[i + 1];
            } else {
                continue;
            }
            break;
        case 0x0b:
            if(cdata.channel == 0 && cdata.list == 0) {
                ((uint8_t*)hm_master_id)[1] = data[i + 1];
            } else {
                continue;
            }
            break;
        case 0x0c:
            if(cdata.channel == 0 && cdata.list == 0) {
                ((uint8_t*)hm_master_id)[2] = data[i + 1];
            } else {
                continue;
            }
            break;
        default:
            continue;
        }

		// wait for eeprom write completion
		while (!(FLASH_IAPSR & FLASH_IAPSR_EOP))
			;
	}

	FLASH_IAPSR &= ~FLASH_IAPSR_DUL;

	return true;
}
