#include "../gpio/gpio.h"

#define KEYPAD_column GPIOC
#define KEYPAD_row GPIOE
#define KEYPAD_COL_PORT PORTE
#define KEYPAD_ROW_PORT PORTC
#define KEYPAD_ROW_NUM 4
#define KEYPAD_COL_NUM 4

void KEYPAD_init(void);
uint8_t KEYPAD_getInput(void);