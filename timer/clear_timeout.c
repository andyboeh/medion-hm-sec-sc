#include "clear_timeout.h"
#include "stm8l.h"
#include <stdbool.h>

extern volatile bool wait_for_timeout;

void clear_timeout(void)
{
    wait_for_timeout = false;
}
