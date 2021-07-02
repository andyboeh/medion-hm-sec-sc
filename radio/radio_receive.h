#ifndef RADIO_RECEIVE_H
#define RADIO_RECEIVE_H

#include "as_packet.h"
#include <stdbool.h>
#include <stdint.h>

bool radio_receive(as_packet_t * pkg, uint8_t max_length);

#endif //RADIO_RECEIVE_H
