#include "clear_singleshot_timer.h"
#include "stm8l.h"

void clear_singleshot_timer() {
    TIM3_SR1 &= ~(1 << 0); // Clear interrupt
    CLK_PCKENR1 &= ~CLK_PCKENR1_TIM3; // Disable clock
}
