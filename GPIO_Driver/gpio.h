#ifndef _GPIO_DRIVER_H
#define _GPIO_DRIVER_H

#include <stdint.h>
#include <math.h>
#include "../comman.h"

#define UNLOCK					0x4C4F434B
#define PORT_OFFSET				0x3FC

// #define I2C_F					0x03
// #define UART_F					0x02

typedef enum GPIORegistersOffset{
	GPIO_DIR 			= 0x400,
	GPIO_IS 			= 0x404,
	GPIO_IBE 			= 0x408,
	GPIO_IEV 			= 0x40C,
	GPIO_IM 			= 0x410,
	GPIO_RIS			= 0x414,
	GPIO_MIS			= 0x418,
	GPIO_ICR			= 0x41C,
	GPIO_AFSEL			= 0x420,
	GPIO_DRV2M			= 0x500,
	GPIO_DRV4M			= 0x504,
	GPIO_DRV8M			= 0x508,
	GPIO_ODR			= 0x50C,
	GPIO_PUR			= 0x510,
	GPIO_PDR			= 0x514,
	GPIO_SLR 			= 0x518,
	GPIO_DEN			= 0x51C,
	GPIO_LCK			= 0x520,
	GPIO_CR				= 0x524,
	GPIO_AMSEL			= 0x528,
	GPIO_PCTL			= 0x52C
} GPIORegistersOffset;

typedef enum Pin{
	PIN0				= 0x001,
	PIN1				= 0x002,
	PIN2				= 0x004,
	PIN3				= 0x008,
	PIN4				= 0x010,
	PIN5				= 0x020,
	PIN6				= 0x040,
	PIN7				= 0x080,
} Pin;

typedef enum PinMode{
	DIGITAL,
	ANALOG ,
} PinMode;

typedef enum PinDir{
	INPUT		 		= 0x00,
	OUTPUT		 		= 0xFF,
	PERIPHERAL,
} PinDir;

typedef enum InterruptEvent{
	RISING,
	FALLING,
	BOTH,
} InterruptEvent;

uint8_t GPIO_readPin(volatile uint32_t portAddress,Pin pin);
void	GPIO_writePin(volatile uint32_t portAddress, Pin pin, uint8_t value);

void 	GPIO_initPort(volatile uint32_t portAddress, PinDir dir);
uint8_t GPIO_readPort(volatile uint32_t portAddress);
void    GPIO_writePort(volatile uint32_t portAddress, uint8_t value);

void 	GPIO_setPullup(volatile uint32_t portAddress, Pin pin);
void 	GPIO_setPulldown(volatile uint32_t portAddress, Pin pin);
void 	GPIO_setPCTL(volatile uint32_t portAddress, Pin pin, uint8_t function);
void 	GPIO_setOpenDrain(volatile uint32_t portAddress, Pin pin);
void 	GPIO_set_drive2m(volatile uint32_t portAddress, Pin pin);
void 	GPIO_set_drive4m(volatile uint32_t portAddress, Pin pin);
void 	GPIO_set_drive8m(volatile uint32_t portAddress, Pin pin);

void 	GPIO_initInterrupt(volatile uint32_t portAddress, Pin pin, InterruptEvent ev, void (*callback)());

#endif
