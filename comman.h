#ifndef _COMMAN_H
#define _COMMAN_H

#define PORTA					0x40004000
#define PORTA_AHB				0x40058000
#define PORTB					0x40005000
#define PORTB_AHB				0x40059000
#define PORTC					0x40006000
#define PORTC_AHB				0x4005A000
#define PORTD					0x40007000
#define PORTD_AHB				0x4005B000
#define PORTE					0x40024000
#define PORTE_AHB				0x4005C000
#define PORTF					0x40025000
#define PORTF_AHB				0x4005D000
	
#define SYSCTL_PRGPIO   		((volatile uint32_t*)0x400FEA08)
#define SYSCTL_RCGCGPIO 		((volatile uint32_t*)0x400FE608)
#define NVIC_EN0            	((volatile uint32_t*)0xE000E100)
#define RCGC2_REG				((volatile uint32_t*)0x400FE108)	

#define HIGH					0xFF
#define LOW						0x00

#define Log(X)					(int)log2(X)
#define Memory(BASE,OFFSET)		(*((volatile uint32_t*)(((uint32_t)BASE)+((uint32_t)OFFSET))))

#endif
