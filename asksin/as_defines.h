#ifndef AS_DEFINES_H
#define AS_DEFINES_H

#include <stdint.h>
#include <stdbool.h>
#include "stm8l.h"

#define AS_HEADER_SIZE 9 // header length without length byte

extern const uint8_t * hm_id;
extern const uint8_t * hm_serial;
extern const uint8_t * hm_master_id;
extern const uint8_t * aes_key;
extern const uint8_t * aes_channel0;
extern const uint8_t * aes_channel1;
extern const uint8_t * aes_key_index;

#ifndef BOOTLOADER
extern bool as_ok;
#endif

#define AS_FLAG_DEF 0x80
#define AS_FLAG_BIDI 0x20

#define CMP_ID(a, b) (((a)[0] == (b)[0] && (a)[1] == (b)[1] && (a)[2] == (b)[2]) ? 0 : 1)
#define ID_IS_NULL(a) (((a)[0] == 0x0 && (a)[1] == 0x0 && (a)[2] == 0x0) ? true : false)
#define LIST_ID(a) (a)[0], (a)[1], (a)[2]
#define LIST_SERIAL(a) (a)[0], (a)[1], (a)[2], (a)[3], (a)[4], (a)[5], (a)[6], (a)[7], (a)[8], (a)[9]

#define CONFIG_START_LENGTH 16
#define CONFIG_WRITE_LENGTH 60
#define CONFIG_END_LENGTH 11
#define MAX_LENGTH CONFIG_WRITE_LENGTH
#ifndef BOOTLOADER
#define MAX_PAYLOAD 60
#else
#define MAX_PAYLOD 37
#endif

#endif //AS_DEFINES_H
