#include "KeyPad.h"

uint8_t characters[KEYPAD_ROW_NUM][KEYPAD_COL_NUM] = {{'1', '2', '3', 'A'},
                                                      {'4', '5', '6', 'B'},
                                                      {'7', '8', '9', 'C'},
                                                      {'*', '0', '#', 'D'}};
uint8_t colValues[KEYPAD_COL_NUM] = {0xE0, 0xD0, 0xB0, 0x70};
uint8_t colWritePort[KEYPAD_ROW_NUM] = {0x1C, 0x1A, 0x16, 0x0E};

void KEYPAD_init(void)
{
    GPIO_PinConfig pinConfig = {KEYPAD_ROW_PORT, PIN4, DIGITAL, INPUT};
    GPIO_initPin(&pinConfig);
    pinConfig.pin = PIN5;
    GPIO_initPin(&pinConfig);
    pinConfig.pin = PIN6;
    GPIO_initPin(&pinConfig);
    pinConfig.pin = PIN7;
    GPIO_initPin(&pinConfig);
    GPIO_setPullup(KEYPAD_ROW_PORT, PIN4);
    GPIO_setPullup(KEYPAD_ROW_PORT, PIN5);
    GPIO_setPullup(KEYPAD_ROW_PORT, PIN6);
    GPIO_setPullup(KEYPAD_ROW_PORT, PIN7);
    GPIO_setOpenDrain(KEYPAD_ROW_PORT, PIN4);
    GPIO_setOpenDrain(KEYPAD_ROW_PORT, PIN5);
    GPIO_setOpenDrain(KEYPAD_ROW_PORT, PIN6);
    GPIO_setOpenDrain(KEYPAD_ROW_PORT, PIN7);

    GPIO_PinConfig pinConfig2 = {KEYPAD_COL_PORT, PIN1, DIGITAL, OUTPUT};
    GPIO_initPin(&pinConfig2);
    pinConfig2.pin = PIN2;
    GPIO_initPin(&pinConfig2);
    pinConfig2.pin = PIN3;
    GPIO_initPin(&pinConfig2);
    pinConfig2.pin = PIN4;
    GPIO_initPin(&pinConfig2);
    GPIO_setOpenDrain(KEYPAD_COL_PORT, PIN1);
    GPIO_setOpenDrain(KEYPAD_COL_PORT, PIN2);
    GPIO_setOpenDrain(KEYPAD_COL_PORT, PIN3);
    GPIO_setOpenDrain(KEYPAD_COL_PORT, PIN4);
}

char KEYPAD_getInput(void)
{
    int col;
    while (1)
    {
        for (int i = 0; i < KEYPAD_ROW_NUM; i++)
        {
            GPIO_writePort(KEYPAD_COL_PORT, colWritePort[i]);
            col = GPIO_readPort(KEYPAD_ROW_PORT) & 0xF0;
            for (int j = 0; j < KEYPAD_COL_NUM; j++)
            {
                if (col == colValues[j])
                {
                    return characters[i][j];
                }
            }
        }

        /*
        // 1st row has zero
        GPIO_writePort(KEYPAD_COL_PORT, 0x1C);
        col = GPIO_readPort(KEYPAD_ROW_PORT) & 0xF0;

        if (col == 0xE0)
        {

            return characters[0][0];
        }
        if (col == 0xD0)
        {
            return characters[0][1];
        }
        if (col == 0xB0)
        {
            return characters[0][2];
        }
        if (col == 0x70)
        {
            return characters[0][3];
        }

        // 2nd row has zero
        GPIO_writePort(KEYPAD_COL_PORT, 0x1A);
        delayMs(100);
        col = GPIO_readPort(KEYPAD_ROW_PORT) & 0xF0;
        if (col == 0xE0)
        {
            return characters[1][0];
        }
        if (col == 0xD0)
        {
            return characters[1][1];
        }
        if (col == 0xB0)
        {
            return characters[1][2];
        }
        if (col == 0x70)
        {
            return characters[1][3];
        }

        // 3rd row has zero
        GPIO_writePort(KEYPAD_COL_PORT, 0x16);
        col = GPIO_readPort(KEYPAD_ROW_PORT) & 0xF0;
        if (col == 0xE0)
        {
            return characters[2][0];
        }
        if (col == 0xD0)
        {
            return characters[2][1];
        }
        if (col == 0xB0)
        {
            return characters[2][2];
        }
        if (col == 0x70)
        {
            return characters[2][3];
        }

        // 4th row has zero
        GPIO_writePort(KEYPAD_COL_PORT, 0x0E);
        col = GPIO_readPort(KEYPAD_ROW_PORT) & 0xF0;

        if (col == 0xE0)
        {
            return characters[3][0];
        }
        if (col == 0xD0)
        {
            return characters[3][1];
        }
        if (col == 0xB0)
        {
            return characters[3][2];
        }
        if (col == 0x70)
        {
            return characters[3][3];
        }*/
    }
}
