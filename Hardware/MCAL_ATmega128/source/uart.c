#ifndef F_CPU
#warning "F_CPU" is not defined, default value will be used, it is adviced to define "F_CPU" in project's compiler macros'
#define F_CPU 1000000UL
#endif // F_CPU

#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"

#define UART_CLK_DIVIDER        8                   /* change to 16 for Normal Mode */

static void (*_Uart0ReceiveCallback)(u8 data);
static void (*_Uart1ReceiveCallback)(u8 data);

ISR(USART0_RX_vect)
{
    _Uart0ReceiveCallback(UDR0);
}
ISR(USART1_RX_vect)
{
    _Uart1ReceiveCallback(UDR1);
}

/// UART 0
void Uart0_Init(u32 baud)
{
    CLR( UCSR0B , BM(TXEN0) | BM(RXEN0) );            /* Disable UART TX/RX */
#if UART_CLK_DIVIDER == 8
    SET( UCSR0A , BM(U2X0) );                         /* Double transfer mode */
#elif UART_CLK_DIVIDER == 16
    CLR( UCSR0A , BM(U2X0) );                         /* Normal transfer mode */
#else
    #error Invalid "UART_CLK_DIVIDER", only values {8,16} are allowed
#endif
    u32 baud_rate= F_CPU/baud/UART_CLK_DIVIDER - 1;     /* change 8 to 16 if U2X mode is disabled */
    UBRR0H = (baud_rate>>8);                            /* baud rate high byte */
    UBRR0L = baud_rate;                                 /* baud rate  low byte */
    SET( UCSR0C, BM(UCSZ10) | BM(UCSZ00) );             /* define data bus size (8 bits) */

    SET( UCSR0B, BM(TXEN0) | BM(RXEN0) );               /* enable transmitter and receiver */
}
void Uart0_CbRecv(void (*receive_cb)(u8 data) )
{
    _Uart0ReceiveCallback=receive_cb;            /* UART ISR function */
    if (receive_cb)
    {
        SET(UCSR0B,BM(RXCIE0));                     /* Enable the USART Receive Complete interrupt (USART_RXC) */
        sei();                                      /* Enable the Global Interrupt Enable flag */
    }
    else
    {
        CLR(UCSR0B,BM(RXCIE0));						/* Enable the USART Receive Complete interrupt (USART_RXC) */
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
    while ( ALL_CLR( UCSR0A , BM(UDRE0) ) );	/* Blocks when a previous transmission is not finished */
    UDR0 = data;								/* Send through UART TX */
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
    while ( ALL_CLR( UCSR0A , BM(RXC0) ) );	/* Blocks until Reception is complete */
    (*data) = UDR0;                         /* Read received byte from UART RX */
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
	while((*size)<buffer_max_size && ALL_SET( UCSR0A , BM(RXC0) ) )
    {
        data[ (*size)++ ]=UDR0;                   /* Read received byte from UART RX */
    }
    return (*size);
}

/// UART 1
void Uart1_Init(u32 baud)
{
    CLR( UCSR1B , BM(TXEN1) | BM(RXEN1) );           /* Disable UART TX/RX */
#if UART_CLK_DIVIDER == 8
    SET( UCSR1A , BM(U2X1) );                        /* Double transfer mode */
#elif UART_CLK_DIVIDER == 16
    CLR( UCSR1A , BM(U2X1) );                        /* Normal transfer mode */
#else
    #error Invalid "UART_CLK_DIVIDER", only values {8,16} are allowed
#endif
    u32 baud_rate= F_CPU/baud/UART_CLK_DIVIDER - 1;     /* change 8 to 16 if U2X mode is disabled */
    UBRR1H = (baud_rate>>8);                            /* baud rate high byte */
    UBRR1L = baud_rate;                                 /* baud rate  low byte */
    SET( UCSR1C, BM(UCSZ11) | BM(UCSZ01) );             /* define data bus size (8 bits) */

    SET( UCSR1B, BM(TXEN1) | BM(RXEN1) );               /* enable transmitter and receiver */
}
void Uart1_CbRecv(void (*receive_cb)(u8 data) )
{
    _Uart1ReceiveCallback=receive_cb;            /* UART ISR function */
    if (receive_cb)
    {
        SET(UCSR1B,BM(RXCIE1));                     /* Enable the USART Receive Complete interrupt (USART_RXC) */
        sei();                                      /* Enable the Global Interrupt Enable flag */
    }
    else
    {
        CLR(UCSR1B,BM(RXCIE1));                     /* Enable the USART Receive Complete interrupt (USART_RXC) */
    }
}
void Uart1_PutA(void* data, u32 size)
{
    u8* _data=(u8*)data;
    u32  byte=0;
    while (byte!=size)
    {
        Uart1_PutC(_data[byte++]);
    }
}
void Uart1_PutC(u8 data)
{
    while ( ALL_CLR( UCSR1A , BM(UDRE1) ) );	/* Blocks when a previous transmission is not finished */
    UDR1 = data;								/* Send through UART TX */
}
void Uart1_PutS(const char* data)
{
    u32 byte=0;
    while (data[byte])
    {
        Uart1_PutC((u8)data[byte++]);
    }
}
void Uart1_GetC(u8* data)
{
    while ( ALL_CLR( UCSR1A , BM(RXC1) ) );	/* Blocks until Reception is complete */
    (*data) = UDR1;                         /* Read received byte from UART RX */
}
void Uart1_GetA(void* data, u32 size)
{
    u8* _data=(u8*)data;
    u32 byte=0;
    for (byte=0;byte<size;byte++)
    {
        Uart1_GetC(_data++);
    }
}
void Uart1_GetS(char* data, u32 size)
{
	do
    {
        Uart1_GetC((u8*)data);
    }while( (*data++!='\n') && --size );
    *data='\0';
}
u8 Uart1_Get(u8* data, u32* size, u32 buffer_max_size)
{
    (*size) = 0;
    while((*size)<buffer_max_size && ALL_SET( UCSR1A , BM(RXC1) ) )
    {
        data[ (*size)++ ]=UDR1;                   /* Read received byte from UART RX */
    }
    return (*size);
}
