#include "set_timeout.h"
#include "get_tick.h"
#include "stm8l.h"
#include <stdbool.h>
extern volatile uint16_t timeout_at;
extern volatile bool wait_for_timeout;

void set_timeout(uint16_t timeout)
{
    timeout_at = timeout;
    wait_for_timeout = true;
}
