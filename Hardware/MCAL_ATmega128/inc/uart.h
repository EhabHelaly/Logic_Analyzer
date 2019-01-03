#ifndef UART_H
#define UART_H

#ifndef F_CPU
#warning "F_CPU" is not defined, default value will be used, it is adviced to define "F_CPU" in project's compiler macros'
#define F_CPU 1000000UL
#endif // F_CPU

#include "std_bit.h"
#include "peripheral.h"

#define UART_MAX_BAUDRATE   (F_CPU/8)   /* Assuming UART double transfer mode is enabled , divide by 16 for normal mode */

#ifndef _INLINE_
#define _INLINE_ static inline __attribute__((always_inline))
#endif /* _INLINE_ */

/* Initialize */
_INLINE_ void Uart_Init(u8 uart, u32 baud);
_INLINE_ void Uart_CbRecv(u8 uart, void (*receive_cb)(u8 data) );
/* Write */
_INLINE_ void Uart_PutC(u8 uart, u8 data);
_INLINE_ void Uart_PutA(u8 uart, void* data, u32 size);
_INLINE_ void Uart_PutS(const u8 uart, const char* data);
/* Read (blocking) */
_INLINE_ void Uart_GetC(u8 uart, u8* data);
_INLINE_ void Uart_GetA(u8 uart, void* data, u32 size);
_INLINE_ void Uart_GetS(u8 uart, char* data, u32 size);
/* Read (non blocking) */
_INLINE_ u8 Uart_Get(u8 uart, u8* data, u32* size, u32 buffer_max_size);

void Uart0_Init(u32 baud);
void Uart0_CbRecv(void (*receive_cb)(u8 data) );
void Uart0_PutC(u8 data);
void Uart0_PutA(void* data, u32 size);
void Uart0_PutS(const char* data);
void Uart0_GetC(u8* data);
void Uart0_GetA(void* data, u32 size);
void Uart0_GetS(char* data, u32 size);
u8   Uart0_Get(u8* data, u32* size, u32 buffer_max_size);

void Uart1_Init(u32 baud);
void Uart1_CbRecv(void (*receive_cb)(u8 data) );
void Uart1_PutC(u8 data);
void Uart1_PutA(void* data, u32 size);
void Uart1_PutS(const char* data);
void Uart1_GetC(u8* data);
void Uart1_GetA(void* data, u32 size);
void Uart1_GetS(char* data, u32 size);
u8   Uart1_Get(u8* data, u32* size, u32 buffer_max_size);

_INLINE_ void Uart_Init(u8 uart, u32 baud)
{
    switch(uart)
    {
        case PERIPHERAL_UART_0: {return Uart0_Init(baud); break;}
        case PERIPHERAL_UART_1: {return Uart1_Init(baud); break;}
        default               : {return                 ; break;}
    }
}
_INLINE_ void Uart_CbRecv(u8 uart, void (*receive_cb)(u8 data) )
{
    switch(uart)
    {
        case PERIPHERAL_UART_0: {return Uart0_CbRecv(receive_cb); break;}
        case PERIPHERAL_UART_1: {return Uart1_CbRecv(receive_cb); break;}
        default               : {return        	    		    ; break;}
    }
}
_INLINE_ void Uart_PutC(u8 uart, u8 data)
{
    switch(uart)
    {
        case PERIPHERAL_UART_0: {return Uart0_PutC(data); break;}
        case PERIPHERAL_UART_1: {return Uart1_PutC(data); break;}
        default               : {return        	        ; break;}
    }
}
_INLINE_ void Uart_PutA(u8 uart, void* data, u32 size)
{
    switch(uart)
    {
        case PERIPHERAL_UART_0: {return Uart0_PutA(data, size); break;}
        case PERIPHERAL_UART_1: {return Uart1_PutA(data, size); break;}
        default               : {return        	 			  ; break;}
    }
}
_INLINE_ void Uart_PutS(const u8 uart, const char* data)
{
    switch(uart)
    {
        case PERIPHERAL_UART_0: {return Uart0_PutS(data); break;}
        case PERIPHERAL_UART_1: {return Uart1_PutS(data); break;}
        default               : {return        	   	    ; break;}
    }
}
_INLINE_ void Uart_GetC(u8 uart, u8* data)
{
    switch(uart)
    {
        case PERIPHERAL_UART_0: {return Uart0_GetC(data); break;}
        case PERIPHERAL_UART_1: {return Uart1_GetC(data); break;}
        default               : {return        	        ; break;}
    }
}
_INLINE_ void Uart_GetA(u8 uart, void* data, u32 size)
{
    switch(uart)
    {
        case PERIPHERAL_UART_0: {return Uart0_GetA(data, size); break;}
        case PERIPHERAL_UART_1: {return Uart1_GetA(data, size); break;}
        default               : {return        	   		      ; break;}
    }
}
_INLINE_ void Uart_GetS(u8 uart, char* data, u32 size)
{
    switch(uart)
    {
        case PERIPHERAL_UART_0: {return Uart0_GetS(data, size); break;}
        case PERIPHERAL_UART_1: {return Uart1_GetS(data, size); break;}
        default               : {return        			      ; break;}
    }
}
_INLINE_ u8 Uart_Get(u8 uart, u8* data, u32* size, u32 buffer_max_size)
{
    switch(uart)
    {
        case PERIPHERAL_UART_0: {return Uart0_Get(data, size, buffer_max_size); break;}
        case PERIPHERAL_UART_1: {return Uart1_Get(data, size, buffer_max_size); break;}
        default               : {return 0      	       						  ; break;}
    }
}

#endif
