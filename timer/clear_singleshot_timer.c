#include "clear_singleshot_timer.h"
#include "stm8l.h"

void clear_singleshot_timer() {
    CLK_PCKENR1 &= ~CLK_PCKENR1_TIM3; // Disable clock
}
