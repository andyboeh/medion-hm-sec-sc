#include "as_set_aes_key_index.h"
#include "as_defines.h"

bool as_set_aes_key_index(uint8_t index) {
    if(index != *aes_key_index) {
        // enable eeprom programming
        FLASH_DUKR = 0xAE;
        FLASH_DUKR = 0x56;
        while (!(FLASH_IAPSR & FLASH_IAPSR_DUL))
            ;
        ((uint8_t*)aes_key_index)[0] = index;
        while (!(FLASH_IAPSR & FLASH_IAPSR_EOP))
            ;

        FLASH_IAPSR &= ~FLASH_IAPSR_DUL;
    }

    return true;
}
