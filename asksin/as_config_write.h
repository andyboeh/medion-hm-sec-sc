#ifndef AS_CONFIG_WRITE_H
#define AS_CONFIG_WRITE_H

#include <stdint.h>
#include <stdbool.h>

bool as_config_write(uint8_t channel, uint8_t length, uint8_t * data);

#endif //AS_CONFIG_WRITE_H
