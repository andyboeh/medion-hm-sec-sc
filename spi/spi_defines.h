#ifndef SPI_DEFINES_H
#define SPI_DEFINES_H

#include "stm8l.h"
#include "medion-hm-sec-sc.h"
#include <stdbool.h>

#define radio_select() do { PB_ODR &= ~nSEL; } while(false)
#define radio_deselect() do { PB_ODR |= nSEL; } while(false)
#define wait_miso() while (PB_IDR & MISO);

#endif //SPI_DEFINES_H
