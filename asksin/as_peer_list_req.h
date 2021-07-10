#ifndef AS_PEER_LIST_REQ
#define AS_PEER_LIST_REQ

#include <stdint.h>
#include "as_packet.h"

void as_peer_list_req(uint8_t channel, as_packet_t *reply_packet);

#endif //AS_PEER_LIST_REQ
