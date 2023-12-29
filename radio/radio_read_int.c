#include "radio_read_int.h"
#include "stm8l.h"
#include "medion-hm-sec-sc.h"

bool radio_read_int(void) {
    return ((bool)(PB_IDR & nIRQ));
}
