#include "as_get_aes_key_index.h"
#include "as_defines.h"

uint8_t as_get_aes_key_index(void) {
    return *aes_key_index;
}
