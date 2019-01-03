#ifndef F_CPU
#warning "F_CPU" is not defined, default value will be used, it is adviced to define "F_CPU" in project's compiler macros'
#define F_CPU 1000000UL
#endif // F_CPU

#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"
#include <math.h>

#define UART_CLK_DIVIDER        8                   /* change to 16 for Normal Mode */

static void (*_UartReceiveCallback)(u8 data);

void Uart0_Init(u32 baud)
{
    CLR( UCSRB , BM(TXEN) | BM(RXEN) );             /* Disable UART TX/RX */
#if UART_CLK_DIVIDER == 8
    SET( UCSRA , BM(U2X) );                         /* Double transfer mode */
#elif UART_CLK_DIVIDER == 16
    CLR( UCSRA , BM(U2X) );                         /* Normal transfer mode */
#else
    #error Invalid "UART_CLK_DIVIDER", only values {8,16} are allowed
#endif
    u32 baud_rate= F_CPU/(baud*UART_CLK_DIVIDER) - 1 ;
    UBRRH = (baud_rate>>8);                         /* baud rate high byte */
    UBRRL = baud_rate;                              /* baud rate  low byte */
    SET( UCSRC, BM(URSEL) | BM(UCSZ1) | BM(UCSZ0) );/* define data bus size (8 bits) */

    SET( UCSRB, BM(TXEN) | BM(RXEN) );              /* enable transmitter and receiver */
}
void Uart0_CbRecv(void (*receive_cb)(u8 data) )
{
    _UartReceiveCallback=receive_cb;            /* UART ISR function */
    if (receive_cb)
    {
        SET(UCSRB,BM(RXCIE));                       /* Enable the USART Receive Complete interrupt (USART_RXC) */
        sei();                                      /* Enable the Global Interrupt Enable flag */
    }
    else
    {
        CLR(UCSRB,BM(RXCIE));                       /* Enable the USART Receive Complete interrupt (USART_RXC) */
    }
}
void Uart0_PutA(void* data, u32 size)
{
    u8* _data=(u8*)data;
    u32  byte=0;
    while (byte!=size)
    {
        Uart0_PutC(_data[byte++]);
    }
}
void Uart0_PutC(u8 data)
{
    while ( ALL_CLR( UCSRA , BM(UDRE) ) );   /* Blocks when a previous transmission is not finished */
    UDR = data;                             /* Send through UART TX */
}
void Uart0_PutS(const char* data)
{
    u32 byte=0;
    while (data[byte])
    {
        Uart0_PutC((u8)data[byte++]);
    }
}

void Uart0_GetC(u8* data)
{
    while ( ALL_CLR( UCSRA , BM(RXC) ) );    /* Blocks until Reception is complete */
    (*data) = UDR;                          /* Read received byte from UART RX */
}
void Uart0_GetA(void* data, u32 size)
{
    u8* _data=(u8*)data;
	u32 byte=0;
	for (byte=0;byte<size;byte++)
    {
        Uart0_GetC(_data++);
    }
}
void Uart0_GetS(char* data, u32 size)
{
	do
    {
        Uart0_GetC((u8*)data);
    }while( (*data++!='\n') && --size );
    *data='\0';
}
u8 Uart0_Get(u8* data, u32* size, u32 buffer_max_size)
{
	(*size) = 0;
	while((*size)<buffer_max_size && ALL_SET( UCSRA , BM(RXC) ) )
    {
        data[ (*size)++ ]=UDR;                   /* Read received byte from UART RX */
    }
    return (*size);
}
ISR(USART_RXC_vect)
{
    _UartReceiveCallback(UDR);
}
