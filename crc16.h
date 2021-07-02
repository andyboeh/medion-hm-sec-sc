#ifndef CRC16_H
#define CRC16_H

#include <stdint.h>

uint16_t crc16(uint16_t crc, uint8_t size, const uint8_t *buf);

#endif //CRC16_H
