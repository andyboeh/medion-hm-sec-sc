#include "as_aes_reply.h"
#include "as_get_aes_key_index.h"
#include <string.h>
#include <stdlib.h>
#include "aes.h"
#include "led_blink.h"

static struct AES_ctx ctx;
static uint8_t temp_hmkey[16];
extern const uint8_t default_aes_key;

static void make_temp_aes_key(const uint8_t *key, uint8_t *challenge) {
    memcpy(temp_hmkey, key, 16);
    for(uint8_t i=0; i<6; i++)
        temp_hmkey[i] ^= challenge[i];
    AES_init_ctx(&ctx, temp_hmkey);
}

static void get_random(uint8_t *buf) {
    for(uint8_t i=0; i<6; i++) {
        buf[i] = rand();
    }
}

void as_aes_reply(as_packet_t * packet, as_packet_t *sent_packet, as_packet_t *reply_packet) {
    uint8_t len;
    len = sent_packet->length - AS_HEADER_SIZE - 1 > 16 ? 16 : sent_packet->length - AS_HEADER_SIZE - 1;

    if(as_get_aes_key_index() == 0) {
        make_temp_aes_key(&default_aes_key, &packet->payload[1]);
    }
    else {
        make_temp_aes_key(aes_key, &packet->payload[1]);
    }

    get_random(reply_packet->payload);
    memcpy(reply_packet->payload + 6, &sent_packet->data[1], 10);

    memset(&ctx.Iv, 0x00, AES_BLOCKLEN);

    // The message is encrypted twice, on first pass
    // with an empty IV, on second pass with the IV
    // set to the payload of the previously sent message
    AES_CBC_encrypt_buffer(&ctx, reply_packet->payload, AES_BLOCKLEN);
    memset(&ctx.Iv, 0x00, AES_BLOCKLEN);
    memcpy(&ctx.Iv, &sent_packet->payload[1], len);

    AES_CBC_encrypt_buffer(&ctx, reply_packet->payload, AES_BLOCKLEN);
    reply_packet->type = 0x03;
    reply_packet->length = AS_HEADER_SIZE + 16;
}
