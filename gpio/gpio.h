#ifndef _GPIO_H
#define _GPIO_H

#include <math.h>
#include "../common.h"
#include "../pin.h"

typedef enum GPIO_InterruptEvent
{
	RISING,
	FALLING,
	BOTH,
} GPIO_InterruptEvent;

typedef struct GPIO_PinConfig
{
	PIN_Port port;
	PIN_Pin pin;
	PIN_PinDir dir;
	PIN_PinMode mode;
} GPIO_PinConfig;

typedef struct GPIO_PortConfig
{
	PIN_Port port;
	PIN_PinDir dir;
} GPIO_PortConfig;

void GPIO_initPin(const GPIO_PinConfig *const config);
uint8_t GPIO_readPin(PIN_Port port, PIN_Pin pin);
void GPIO_writePin(PIN_Port port, PIN_Pin pin, uint8_t value);
void GPIO_initPort(GPIO_PortConfig *config);
uint8_t GPIO_readPort(PIN_Port port);
void GPIO_writePort(PIN_Port port, uint8_t value);
void GPIO_setPullup(PIN_Port port, PIN_Pin pin);
void GPIO_setPulldown(PIN_Port port, PIN_Pin pin);
void GPIO_initInterrupt(PIN_Port port, PIN_Pin pin, InterruptEvent ev, void (*callback)());

#endif
