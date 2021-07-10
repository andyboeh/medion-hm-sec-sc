#include "as_factory_reset.h"
#include "stm8l.h"
#include "as_defines.h"
#include <stdint.h>

static void write_value(const uint8_t * address, uint8_t value) {
    ((uint8_t*)address)[0] = value;
    while (!(FLASH_IAPSR & FLASH_IAPSR_EOP))
        ;

}

void as_factory_reset() {
    // enable eeprom programming
    FLASH_DUKR = 0xAE;
    FLASH_DUKR = 0x56;
    while (!(FLASH_IAPSR & FLASH_IAPSR_DUL))
        ;
    write_value(hm_master_id, 0x00);
    write_value(hm_master_id+1, 0x00);
    write_value(hm_master_id+2, 0x00);
    for(int i=0; i<16; i++) {
        write_value(aes_key+i, 0x00);
    }
    write_value(aes_channel0, 0x00);
    write_value(aes_channel1, 0x00);
    write_value(aes_key_index, 0x00);
    write_value(cyclic_info, 0x00);

    FLASH_IAPSR &= ~FLASH_IAPSR_DUL;
}
