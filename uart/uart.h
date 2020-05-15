
#ifndef _UART_H
#define _UART_H

#include <stdint.h>
#include "gpio.h"
#include "../common.h"
#include "../pin.h"
#include <string.h>
#include <stdlib.h>

#define CLK_SPEED 50000000
#define UART_BUFFER_SIZE 64
#define BAUD_IDIV(B) (int)(CLK_SPEED / (16 * B))
#define BAUD_FDIV(B) (int)(((CLK_SPEED / (16 * B)) - BAUD_IDIV(B)) * 64)
#define UART_CLK ((volatile uint32_t *)0x400FE618)
#define RCGC2_REG ((volatile uint32_t *)0x400FE108) //really don't know why we are using this

typedef enum UART_Uart
{
    UART0 = 0x4000C000,
    UART1 = 0x4000D000,
    UART2 = 0x4000E000,
    UART3 = 0x4000F000,
    UART4 = 0x40010000,
    UART5 = 0x40011000,
    UART6 = 0x40012000,
    UART7 = 0x40013000,
} UART_Uart;

typedef enum UART_RegistersOffset
{
    UART_DATA = 0x000,
    UART_RS_EC = 0x004,
    UART_FLAG = 0x018,
    UART_IBRD = 0x024,
    UART_FBRD = 0x028,
    UART_LCTL = 0x02C,
    UART_CTL = 0x030,
    UART_IFLS = 0x034,
    UART_IM = 0x038,
    UART_RIS = 0x03C,
    UART_MIS = 0x040,
    UART_IC = 0x044,
    UART_DMACTL = 0x048,
    UART_PP = 0xFC0,
    UART_CC = 0xFC8,
} UART_RegistersOffset;

typedef enum UART_Baudrate
{
    UART_BAUD_300 = 300,
    UART_BAUD_1200 = 1200,
    UART_BAUD_2400 = 2400,
    UART_BAUD_4800 = 4800,
    UART_BAUD_9600 = 9600,
    UART_BAUD_19200 = 19200,
    UART_BAUD_38400 = 38400,
    UART_BAUD_57600 = 57600,
    UART_BAUD_74880 = 74880,
    UART_BAUD_115200 = 115200,
} UART_Baudrate;

void UART_init(UART_Uart uart, UART_Baudrate baudrate);
uint8_t UART_readChar(UART_Uart uart);
void UART_sendChar(UART_Uart uart, const uint8_t data);
void UART_sendString(UART_Uart uart, const uint8_t *data);
void UART_sendByteStream(UART_Uart uart, const uint8_t *data, const uint8_t size);
void UART_attachBuffer(UART_Uart uart);
void UART_interruptHandler(UART_Uart uart);
void UART_readString(uint8_t *dest);
uint8_t UART_bufferAvailable();
#endif