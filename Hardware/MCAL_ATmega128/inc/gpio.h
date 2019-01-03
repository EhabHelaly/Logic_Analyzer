#ifndef GPIO_H_INC
#define GPIO_H_INC

#include "std_bit.h"
#include "peripheral.h"
#include <avr/io.h>

/* GPIO Configuration */
#define GPIO_CONFIG_INPPUT     	        0x01
#define GPIO_CONFIG_OUTPPUT             0x02
#define GPIO_CONFIG_NO_PULL             0x04
#define GPIO_CONFIG_PULL_UP             0x08
/* Peripheral GPIO Configuration */
#define GPIO_CONFIG_I2C_PULL_UP         0x01
#define GPIO_CONFIG_SPI_MASTER          0x01
#define GPIO_CONFIG_SPI_SLAVE           0x02
#define GPIO_CONFIG_ADC_CH(channel)     BM(channel)
#define GPIO_CONFIG_TIMER_OCA           0x01
#define GPIO_CONFIG_TIMER_OCB           0x02
#define GPIO_CONFIG_TIMER_OCC           0x04
#define GPIO_CONFIG_TIMER_T             0x08
#define GPIO_CONFIG_DEFAULT             0xFF

#ifndef _INLINE_
#define _INLINE_ static inline __attribute__((always_inline))
#endif /* _INLINE_ */

void Gpio_Init(u8 port, u8 pin_mask, u8 configuration);

void Gpio_InitTimer0(u16 configuration);
void Gpio_InitTimer1(u16 configuration);
void Gpio_InitTimer2(u16 configuration);
void Gpio_InitTimer3(u16 configuration);
void Gpio_InitSpi0(u16 configuration);
void Gpio_InitAdc0(u16 configuration);

_INLINE_ void Gpio_InitPeripheral(u8 peripheral, u16 configuration);

_INLINE_ void Gpio_Set (u8 port, u8 pin_mask);
_INLINE_ void Gpio_Clr (u8 port, u8 pin_mask);
_INLINE_ void Gpio_Tgl (u8 port, u8 pin_mask);
_INLINE_ void Gpio_Put (u8 port, u8 pin_mask, u8 masked_value);
_INLINE_ u8   Gpio_Get (u8 port);

_INLINE_ void Gpio_InitPeripheral(u8 peripheral, u16 configuration)
{
    switch(peripheral)
    {
        case PERIPHERAL_TIMER_0:{ Gpio_InitTimer0(configuration);       break; }
        case PERIPHERAL_TIMER_1:{ Gpio_InitTimer1(configuration);       break; }
        case PERIPHERAL_TIMER_2:{ Gpio_InitTimer2(configuration);       break; }
        case PERIPHERAL_TIMER_3:{ Gpio_InitTimer3(configuration);       break; }
        case PERIPHERAL_UART_0:{ /* No Initialization Required */       break; }
        case PERIPHERAL_UART_1:{ /* No Initialization Required */       break; }
        case PERIPHERAL_I2C_0:{ /* No Initialization Required */       break; }
        case PERIPHERAL_SPI_0:{ Gpio_InitSpi0(configuration);       break; }
        case PERIPHERAL_ADC_0:{ Gpio_InitAdc0(configuration);       break; }
        case PERIPHERAL_INT_0:{ /* No Initialization Required */       break; }
        case PERIPHERAL_INT_1:{ /* No Initialization Required */       break; }
        case PERIPHERAL_INT_2:{ /* No Initialization Required */       break; }
        case PERIPHERAL_INT_3:{ /* No Initialization Required */       break; }
        case PERIPHERAL_INT_4:{ /* No Initialization Required */       break; }
        case PERIPHERAL_INT_5:{ /* No Initialization Required */       break; }
        case PERIPHERAL_INT_6:{ /* No Initialization Required */       break; }
        case PERIPHERAL_INT_7:{ /* No Initialization Required */       break; }
        default        		 :{ /* No Initialization Required */       break; }
    }
}

_INLINE_ void Gpio_Set (u8 port, u8 pin_mask)
{
    switch(port)
    {
        case PERIPHERAL_GPIO_A:{ SET(PORTA,pin_mask); break; }
        case PERIPHERAL_GPIO_B:{ SET(PORTB,pin_mask); break; }
        case PERIPHERAL_GPIO_C:{ SET(PORTC,pin_mask); break; }
        case PERIPHERAL_GPIO_D:{ SET(PORTD,pin_mask); break; }
        case PERIPHERAL_GPIO_E:{ SET(PORTE,pin_mask); break; }
        case PERIPHERAL_GPIO_F:{ SET(PORTF,pin_mask); break; }
        case PERIPHERAL_GPIO_G:{ SET(PORTG,pin_mask); break; }
        default        		  :{ /* No Action*/       break; }
    }
}
_INLINE_ void Gpio_Clr (u8 port, u8 pin_mask)
{
    switch(port)
    {
        case PERIPHERAL_GPIO_A:{ CLR(PORTA,pin_mask); break; }
        case PERIPHERAL_GPIO_B:{ CLR(PORTB,pin_mask); break; }
        case PERIPHERAL_GPIO_C:{ CLR(PORTC,pin_mask); break; }
        case PERIPHERAL_GPIO_D:{ CLR(PORTD,pin_mask); break; }
        case PERIPHERAL_GPIO_E:{ CLR(PORTE,pin_mask); break; }
        case PERIPHERAL_GPIO_F:{ CLR(PORTF,pin_mask); break; }
        case PERIPHERAL_GPIO_G:{ CLR(PORTG,pin_mask); break; }
        default      		  :{ /* No Action*/       break; }
    }
}
_INLINE_ void Gpio_Tgl (u8 port, u8 pin_mask)
{
    switch(port)
    {
        case PERIPHERAL_GPIO_A:{ TGL(PORTA,pin_mask); break; }
        case PERIPHERAL_GPIO_B:{ TGL(PORTB,pin_mask); break; }
        case PERIPHERAL_GPIO_C:{ TGL(PORTC,pin_mask); break; }
        case PERIPHERAL_GPIO_D:{ TGL(PORTD,pin_mask); break; }
        case PERIPHERAL_GPIO_E:{ TGL(PORTE,pin_mask); break; }
        case PERIPHERAL_GPIO_F:{ TGL(PORTF,pin_mask); break; }
        case PERIPHERAL_GPIO_G:{ TGL(PORTG,pin_mask); break; }
        default         	  :{ /* No Action*/       break; }
    }

}
_INLINE_ void Gpio_Put (u8 port, u8 pin_mask, u8 masked_value)
{
    switch(port)
    {
        case PERIPHERAL_GPIO_A:{ PUT(PORTA,pin_mask,masked_value); break; }
        case PERIPHERAL_GPIO_B:{ PUT(PORTB,pin_mask,masked_value); break; }
        case PERIPHERAL_GPIO_C:{ PUT(PORTC,pin_mask,masked_value); break; }
        case PERIPHERAL_GPIO_D:{ PUT(PORTD,pin_mask,masked_value); break; }
        case PERIPHERAL_GPIO_E:{ PUT(PORTE,pin_mask,masked_value); break; }
        case PERIPHERAL_GPIO_F:{ PUT(PORTF,pin_mask,masked_value); break; }
        case PERIPHERAL_GPIO_G:{ PUT(PORTG,pin_mask,masked_value); break; }
        default         	  :{ /* No Action*/                    break; }
    }
}
_INLINE_ u8 Gpio_Get (u8 port)
{
    u8 ReadPort=0;
    switch(port)
    {
        case PERIPHERAL_GPIO_A:{ ReadPort = PINA ; break; }
        case PERIPHERAL_GPIO_B:{ ReadPort = PINB ; break; }
        case PERIPHERAL_GPIO_C:{ ReadPort = PINC ; break; }
        case PERIPHERAL_GPIO_D:{ ReadPort = PIND ; break; }
        case PERIPHERAL_GPIO_E:{ ReadPort = PINE ; break; }
        case PERIPHERAL_GPIO_F:{ ReadPort = PINF ; break; }
        case PERIPHERAL_GPIO_G:{ ReadPort = PING ; break; }
        default         	  :{ /* No Action*/    break; }
    }
    return ReadPort;
}

#endif // GPIO_H_INC
