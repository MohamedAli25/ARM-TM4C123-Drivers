#include "pin.h"

void PIN_setClkSource(PIN_Port port)
{
    switch (port)
    {
    case PORTA:
        RCGC2_REG |= 0x01;
        SYSCTL_RCGCGPIO_REG |= 0x01;
        while (!(SYSCTL_PRGPIO_REG |= 0x01))
            ;
        break;
    case PORTB:
        RCGC2_REG |= 0x02;
        SYSCTL_RCGCGPIO_REG |= 0x02;
        while (!(SYSCTL_PRGPIO_REG |= 0x02))
            ;
        break;
    case PORTC:
        RCGC2_REG |= 0x04;
        SYSCTL_RCGCGPIO_REG |= 0x04;
        while (!(SYSCTL_PRGPIO_REG & 0x00000004))
            ;
        break;
    case PORTD:
        RCGC2_REG |= 0x08;
        SYSCTL_RCGCGPIO_REG |= 0x08;
        while (!(SYSCTL_PRGPIO_REG |= 0x08))
            ;
        break;
    case PORTE:
        RCGC2_REG |= 0x10;
        SYSCTL_RCGCGPIO_REG |= 0x10;
        while (!(SYSCTL_PRGPIO_REG |= 0x10))
            ;
        break;
    case PORTF:
        RCGC2_REG |= 0x20;
        SYSCTL_RCGCGPIO_REG |= 0x20;
        while (!(SYSCTL_PRGPIO_REG |= 0x20))
            ;
        break;
    }
}

void PIN_initPin(const PIN_PinConfig *const pinConfig)
{
    PIN_setClkSource(pinConfig->port);
    Memory(pinConfig->port, LCK) = UNLOCK;
    Memory(pinConfig->port, CR) |= pinConfig->pin;
    if (pinConfig->mode == DIGITAL)
    {
        Memory(pinConfig->port, DEN) |= pinConfig->pin;
        Memory(pinConfig->port, AMSEL) &= ~(pinConfig->pin);
    }
    else
    {
        Memory(pinConfig->port, DEN) &= ~(pinConfig->pin);
        Memory(pinConfig->port, AMSEL) |= pinConfig->pin;
    }
    if (pinConfig->dir == OUTPUT)
    {
        Memory(pinConfig->port, DIR) |= pinConfig->pin;
        Memory(pinConfig->port, AFSEL) &= ~(pinConfig->pin);
    }
    else if (pinConfig->dir == INPUT)
    {
        Memory(pinConfig->port, DIR) &= ~(pinConfig->pin);
        Memory(pinConfig->port, AFSEL) &= ~(pinConfig->pin);
    }
    else if (pinConfig->dir == PERIPHERAL)
    {
        Memory(pinConfig->port, AFSEL) |= (pinConfig->pin);
    }
}

void PIN_initPort(const PIN_PortConfig *const portConfig)
{
    PIN_setClkSource(portConfig->port);
    Memory(portConfig->port, LCK) = UNLOCK;
    Memory(portConfig->port, CR) = 0xFF;
    Memory(portConfig->port, DEN) = 0xFF;
    Memory(portConfig->port, AMSEL) = 0x00;
    Memory(portConfig->port, AFSEL) = 0x00;
    Memory(portConfig->port, PCTL) = 0x00;
    Memory(portConfig->port, DIR) = portConfig->dir;
}

void PIN_setPullup(PIN_Port port, PIN_Pin pin)
{
    Memory(port, PUR) |= pin;
}

void PIN_setPulldown(PIN_Port port, PIN_Pin pin)
{
    Memory(port, PDR) |= pin;
}

void PIN_setPCTL(PIN_Port port, PIN_Pin pin, uint8_t function)
{
    // TODO: must clarify this line
    Memory(port, PCTL) = (Memory(port, PCTL) & (~(0x0000000F << (Log(pin) * 4)))) | (function << ((Log(pin) * 4)));
}

void PIN_setOpenDrain(PIN_Port port, PIN_Pin pin)
{
    Memory(port, ODR) |= pin;
}

void PIN_setDrive2m(PIN_Port port, PIN_Pin pin)
{
    Memory(port, DRV2M) |= pin;
}
void PIN_setDrive4m(PIN_Port port, PIN_Pin pin)
{
    Memory(port, DRV4M) |= pin;
}
void PIN_setDrive8m(PIN_Port port, PIN_Pin pin)
{
    Memory(port, DRV8M) |= pin;
}
