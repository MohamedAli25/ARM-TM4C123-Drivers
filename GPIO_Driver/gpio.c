#include "gpio.h"

void (*callbackTable[6][8])();

void GPIO_setClkSource(PIN_Port port)
{
	PIN_setClkSource(port);
}

void GPIO_initPin(const GPIO_PinConfig *const config)
{
	PIN_PinConfig pinConfig = {
		config->port,
		config->pin,
		config->dir,
		config->mode,
	};
	PIN_initPin(&pinConfig);
}

uint8_t GPIO_readPin(PIN_Port port, PIN_Pin pin)
{
	return Memory(port, PORT_OFFSET) & pin;
}

void GPIO_writePin(PIN_Port port, PIN_Pin pin, uint8_t value)
{
	Memory(port, (PIN_Pin << 2)) = value;
}

void GPIO_initPort(GPIO_PinConfig *config)
{
	PIN_PortConfig portConfig = {config->port, config->dir};
	PIN_initPort(&portConfig);
}

uint8_t GPIO_readPort(PIN_Port port)
{
	return Memory(port, PORT_OFFSET);
}

void GPIO_writePort(PIN_Port port, uint8_t value)
{
	Memory(port, PORT_OFFSET) = value;
}

void GPIO_setPullup(PIN_Port port, PIN_Pin pin)
{
	PIN_setPullup(port, pin);
}

void GPIO_setPulldown(PIN_Port port, PIN_Pin pin)
{
	PIN_setPulldown(port, pin);
}

void GPIO_initInterrupt(PIN_Port port, PIN_Pin pin, InterruptEvent ev, void (*callback)())
{
	GPIO_setClkSource(port);
	Memory(port, IS) &= ~(pin);
	if (ev == BOTH)
	{
		Memory(port, IBE) |= (pin);
	}
	else if (ev == FALLING)
	{
		Memory(port, IBE) &= ~(pin);
		Memory(port, IEV) &= ~(pin);
	}
	else if (ev == RISING)
	{
		Memory(port, IBE) &= ~(pin);
		Memory(port, IEV) |= (pin);
	}
	Memory(port, ICR) |= (pin);
	Memory(port, IM) |= (pin);
	switch (port)
	{
	case PORTA:
		(*NVIC_EN0) |= (1 << 0);
		callbackTable[0][Log(pin)] = callback;
		break;
	case PORTB:
		(*NVIC_EN0) |= (1 << 1);
		callbackTable[1][Log(pin)] = callback;
		break;
	case PORTC:
		(*NVIC_EN0) |= (1 << 2);
		callbackTable[2][Log(pin)] = callback;
		break;
	case PORTD:
		(*NVIC_EN0) |= (1 << 3);
		callbackTable[3][Log(pin)] = callback;
		break;
	case PORTE:
		(*NVIC_EN0) |= (1 << 4);
		callbackTable[4][Log(pin)] = callback;
		break;
	case PORTF:
		(*NVIC_EN0) |= (1 << 30);
		callbackTable[5][Log(pin)] = callback;
		break;
	}
}

void GPIO_interruptHandler(PIN_Port port)
{
	uint8_t portNumber;
	switch (port)
	{
	case PORTA:
		portNumber = 0;
		break;
	case PORTB:
		portNumber = 1;
		break;
	case PORTC:
		portNumber = 2;
		break;
	case PORTD:
		portNumber = 3;
		break;
	case PORTE:
		portNumber = 4;
		break;
	case PORTF:
		portNumber = 5;
		break;
	}
	if (Memory(port, MIS) == PIN0)
	{
		Memory(port, ICR) |= PIN0;
		callbackTable[portNumber][0]();
	}
	else if (Memory(port, MIS) == PIN1)
	{
		Memory(port, ICR) |= PIN1;
		callbackTable[portNumber][1]();
	}
	else if (Memory(port, MIS) == PIN2)
	{
		Memory(port, ICR) |= PIN2;
		callbackTable[portNumber][2]();
	}
	else if (Memory(port, MIS) == PIN3)
	{
		Memory(port, ICR) |= PIN3;
		callbackTable[portNumber][3]();
	}
	else if (Memory(port, MIS) == PIN4)
	{
		Memory(port, ICR) |= PIN4;
		callbackTable[portNumber][4]();
	}
	else if (Memory(port, MIS) == PIN5)
	{
		Memory(port, ICR) |= PIN5;
		callbackTable[portNumber][5]();
	}
	else if (Memory(port, MIS) == PIN6)
	{
		Memory(port, ICR) |= PIN6;
		callbackTable[portNumber][6]();
	}
	else if (Memory(port, MIS) == PIN7)
	{
		Memory(port, ICR) |= PIN7;
		callbackTable[portNumber][7]();
	}
}

void GPIOA_Handler()
{
	GPIO_interruptHandler(PORTA);
}

void GPIOB_Handler()
{
	GPIO_interruptHandler(PORTB);
}

void GPIOC_Handler()
{
	GPIO_interruptHandler(PORTC);
}

void GPIOD_Handler()
{
	GPIO_interruptHandler(PORTD);
}

void GPIOE_Handler()
{
	GPIO_interruptHandler(PORTE);
}

void GPIOF_Handler()
{
	GPIO_interruptHandler(PORTF);
}
