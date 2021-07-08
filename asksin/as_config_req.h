#ifndef AS_CONFIG_REQ_H
#define AS_CONFIG_REQ_H

#include <stdint.h>
#include "as_packet.h"

void as_config_req(uint8_t channel, uint8_t list, as_packet_t *reply_packet);

#endif //AS_CONFIG_REQ_H
