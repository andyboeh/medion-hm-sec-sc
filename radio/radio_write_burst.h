#ifndef RADIO_WRITE_BURST_H
#define RADIO_WRITE_BURST_H

#include <stdint.h>

void radio_write_burst(uint8_t addr, uint8_t len, uint8_t * data);

#endif //RADIO_WRITE_BURST_H
