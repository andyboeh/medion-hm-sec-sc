#include "as_set_new_aes_key.h"
#include "as_set_aes_key_index.h"
#include "as_get_aes_key_index.h"
#include "aes.h"
#include <string.h>

extern const uint8_t * aes_key;
static uint8_t new_aes_key[16];
static uint8_t new_aes_key_index = 0;
const uint8_t default_aes_key[16] = {
    0xA4,
    0xE3,
    0x75,
    0xC6,
    0xB0,
    0x9F,
    0xD1,
    0x85,
    0xF2,
    0x7C,
    0x4E,
    0x96,
    0xFC,
    0x27,
    0x3A,
    0xE4
};

static void as_write_aes_key() {
    FLASH_DUKR = 0xAE;
    FLASH_DUKR = 0x56;

    while (!(FLASH_IAPSR & FLASH_IAPSR_DUL))
        ;
    for(int i=0; i<16; i++) {
        if(aes_key[i] != new_aes_key[i]) {
            ((uint8_t*)aes_key)[i] = new_aes_key[i];
            while (!(FLASH_IAPSR & FLASH_IAPSR_EOP))
                ;
        }
    }
    FLASH_IAPSR &= ~FLASH_IAPSR_DUL;
}

bool as_set_new_aes_key(as_packet_t *packet) {
    struct AES_ctx ctx;
    if(as_get_aes_key_index() == 0) {
        AES_init_ctx(&ctx, default_aes_key);
    } else {
        AES_init_ctx(&ctx, aes_key);
    }
    AES_CBC_decrypt_buffer(&ctx, packet->payload, packet->length - AS_HEADER_SIZE);
    if(packet->payload[0] != 0x01)
        return false;
    uint8_t slice = packet->payload[1] & 1;
    memcpy(new_aes_key + (slice * 8), &packet->payload[2], 8);
    new_aes_key_index = packet->payload[1] & 0xfe;
    if(slice) {
        as_set_aes_key_index(new_aes_key_index);
        as_write_aes_key();
    }
    return true;
}
