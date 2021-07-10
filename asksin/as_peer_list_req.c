#include "as_peer_list_req.h"

void as_peer_list_req(uint8_t channel, as_packet_t *reply_packet) {
    // We do not support peering, so we just send an empty answer for now.
    reply_packet->payload[0] = channel;
    reply_packet->payload[1] = 0x00;
    reply_packet->payload[2] = 0x00;
    reply_packet->payload[3] = 0x00;
    reply_packet->payload[4] = 0x00;
    reply_packet->length = AS_HEADER_SIZE + 1 + 4;
    reply_packet->type = 0x10;
}
