#ifndef BUTTON_ISR_H
#define BUTTON_ISR_H

void button_isr() __interrupt(13);
void handle_button_pressed();
void handle_button_released();

#endif //BUTTON_ISR_H
