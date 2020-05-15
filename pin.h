#ifndef _PIN_H
#define _PIN_H

#include "common.h"

#define I2C_F 0x03
#define UART_F 0x02

#define UNLOCK 0x4C4F434B
#define PORT_OFFSET 0x3FC

typedef enum PIN_Port
{
	PORTA = 0x40004000,
	PORTB = 0x40005000,
	PORTC = 0x40006000,
	PORTD = 0x40007000,
	PORTE = 0x40024000,
	PORTF = 0x40025000,
	PORTA_AHB = 0x40058000,
	PORTB_AHB = 0x40059000,
	PORTC_AHB = 0x4005A000,
	PORTD_AHB = 0x4005B000,
	PORTE_AHB = 0x4005C000,
	PORTF_AHB = 0x4005D000,
} PIN_Port;

typedef enum PIN_Pin
{
	PIN0 = 0x001,
	PIN1 = 0x002,
	PIN2 = 0x004,
	PIN3 = 0x008,
	PIN4 = 0x010,
	PIN5 = 0x020,
	PIN6 = 0x040,
	PIN7 = 0x080,
} PIN_Pin;

typedef enum PIN_PinMode
{
	DIGITAL,
	ANALOG,
} PIN_PinMode;

typedef enum PIN_PinDir
{
	INPUT = 0x00,
	OUTPUT = 0xFF,
	PERIPHERAL,
} PIN_PinDir;

typedef enum PIN_RegistersOffset
{
	DIR = 0x400,
	IS = 0x404,
	IBE = 0x408,
	IEV = 0x40C,
	IM = 0x410,
	RIS = 0x414,
	MIS = 0x418,
	ICR = 0x41C,
	AFSEL = 0x420,
	DRV2M = 0x500,
	DRV4M = 0x504,
	DRV8M = 0x508,
	ODR = 0x50C,
	PUR = 0x510,
	PDR = 0x514,
	SLR = 0x518,
	DEN = 0x51C,
	LCK = 0x520,
	CR = 0x524,
	AMSEL = 0x528,
	PCTL = 0x52C
} PIN_RegistersOffset;

typedef struct PIN_PinConfig
{
	PIN_Port port;
	PIN_Pin pin;
	PIN_PinDir dir;
	PIN_PinMode mode;
} PIN_PinConfig;

typedef struct PIN_PortConfig
{
	PIN_Port port;
	PIN_PinDir dir;
} PIN_PortConfig;

void PIN_setClkSource(PIN_Port port);
void PIN_initPin(const PIN_PinConfig *const pinConfig);
void PIN_initPort(const PIN_PortConfig *const portConfig);
void PIN_setPullup(PIN_Port port, PIN_Pin pin);
void PIN_setPulldown(PIN_Port port, PIN_Pin pin);
void PIN_setPCTL(PIN_Port port, PIN_Pin pin, uint8_t function);
void PIN_setOpenDrain(PIN_Port port, PIN_Pin pin);
void PIN_setDrive2m(PIN_Port port, PIN_Pin pin);
void PIN_setDrive4m(PIN_Port port, PIN_Pin pin);
void PIN_setDrive8m(PIN_Port port, PIN_Pin pin);

#endif