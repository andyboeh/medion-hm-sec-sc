#include "wait_timeout.h"
#include "stm8l.h"
#include <stdbool.h>

extern volatile bool wait_for_timeout;

void wait_timeout()
{
    while (wait_for_timeout)
        wfi();
}
