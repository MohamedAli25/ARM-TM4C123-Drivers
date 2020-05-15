#ifndef _COMMON_H
#define _COMMON_H

#include <stdint.h>

#define PORTA_BASE 0x40004000
#define PORTA_AHB_BASE 0x40058000
#define PORTB_BASE 0x40005000
#define PORTB_AHB_BASE 0x40059000
#define PORTC_BASE 0x40006000
#define PORTC_AHB_BASE 0x4005A000
#define PORTD_BASE 0x40007000
#define PORTD_AHB_BASE 0x4005B000
#define PORTE_BASE 0x40024000
#define PORTE_AHB_BASE 0x4005C000
#define PORTF_BASE 0x40025000
#define PORTF_AHB_BASE 0x4005D000

#define SYSCTL_PRGPIO_REG (*(volatile uint32_t *const)0x400FEA08)
#define SYSCTL_RCGCGPIO_REG (*(volatile uint32_t *const)0x400FE608)
#define NVIC_EN0_REG (*(volatile uint32_t *const)0xE000E100)
#define RCGC2_REG (*(volatile uint32_t *const)0x400FE108)

#define HIGH 0xFF
#define LOW 0x00

#define Log(X) ((int)log2(X))
#define Memory(BASE, OFFSET) (*((volatile uint32_t *const)(((uint32_t)BASE) + ((uint32_t)OFFSET))))

#endif
