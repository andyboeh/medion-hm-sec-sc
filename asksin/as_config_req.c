#include "as_config_req.h"
#include "as_defines.h"
#include <stdbool.h>

void as_config_req(uint8_t channel, uint8_t list, as_packet_t *reply_packet) {
    if(channel == 1 && list == 1) {
        reply_packet->type = 0x10;
        reply_packet->length = AS_HEADER_SIZE + 6;
        reply_packet->payload[0] = channel;
        reply_packet->payload[1] = 0x02;
        reply_packet->payload[2] = 0x08; // AES encryption
        reply_packet->payload[3] = *aes_channel1;
        reply_packet->payload[4] = 0x00;
        reply_packet->payload[5] = 0x00;
    } else {
        reply_packet->payload[0] = 0x80; // Set payload to NACK
    }
}
