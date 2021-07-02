#ifndef AS_CONFIG_DATA_H
#define AS_CONFIG_DATA_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t channel;
    uint8_t list;
    bool active;
} config_data;

#endif //AS_CONFIG_DATA_H
