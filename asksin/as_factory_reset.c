#include "as_factory_reset.h"
#include "stm8l.h"
#include "as_defines.h"
#include <stdint.h>

static void write_value(const uint8_t * address, uint8_t value) {
    ((uint8_t*)address)[0] = value;
    while (!(FLASH_IAPSR & FLASH_IAPSR_EOP))
        ;

}

void as_factory_reset(void) {
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
    write_value(sabotage_message, 0x01);
    write_value(transmit_try_max, 0x06);
    write_value(link_channel1, 0x00);
    write_value(link_channel2, 0x00);
    write_value(link_channel3, 0x00);
    write_value(link_channel4, 0x00);
    for(int i=0; i<3; i++) {
        write_value(link_address1+i, 0x00);
        write_value(link_address2+i, 0x00);
        write_value(link_address3+i, 0x00);
        write_value(link_address4+i, 0x00);
    }
    write_value(msg_for_pos, 0x60);
    write_value(event_delay_time, 0x00);
    write_value(led_on_time, 0x64);
    write_value(peer_transmit_try_max, 0x06);

    FLASH_IAPSR &= ~FLASH_IAPSR_DUL;
}
