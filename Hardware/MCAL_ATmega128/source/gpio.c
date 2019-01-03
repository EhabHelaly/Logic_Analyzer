#include "gpio.h"

void Gpio_Init(u8 port, u8 pin_mask, u8 configuration)
{
    volatile u8* GPIO_Dir [] = {& DDRA, & DDRB, & DDRC, & DDRD, & DDRE, & DDRF, & DDRG};
    volatile u8* GPIO_Port[] = {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE, &PORTF, &PORTG};

	if(port<=PERIPHERAL_GPIO_G)
    {
        if( ALL_SET(configuration,GPIO_CONFIG_OUTPPUT) )
        {
            SET( *GPIO_Dir[port] , pin_mask );
        }
        else    /// GPIO_INPUT
        {
            CLR( *GPIO_Dir[port] , pin_mask );
            if( ALL_SET(configuration,GPIO_CONFIG_PULL_UP) )
            {
                SET( *GPIO_Port[port] , pin_mask );
            }
            else    /// GPIO_NO_PULL
            {
                CLR( *GPIO_Port[port] , pin_mask );
            }
        }
    }
}

void Gpio_InitTimer0(u16 configuration)
{

}
void Gpio_InitTimer1(u16 configuration)
{

}
void Gpio_InitTimer2(u16 configuration)
{

}
void Gpio_InitTimer3(u16 configuration)
{

}
void Gpio_InitSpi0(u16 configuration)
{

}
void Gpio_InitAdc0(u16 configuration)
{

}
