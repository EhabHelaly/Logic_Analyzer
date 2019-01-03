#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#ifndef F_CPU
#warning "F_CPU" is not defined, default value will be used, it is adviced to define "F_CPU" in project's compiler macros'
#define F_CPU 1000000UL
#endif // F_CPU

#include "std_bit.h"
#include "peripheral.h"
#include <util/delay.h>

#define DELAY_MS(time)      _delay_ms(time)
#define DELAY_US(time)      _delay_us(time)


#define TIMER_MODE_NORMAL   0x00
#define TIMER_MODE_PWM      0x01
#define TIMER_MODE_CTC      0x02
#define TIMER_MODE_FAST_PWM 0x03

#define TIMER_EXT_CLK_FALL_EDGE       0x04
#define TIMER_EXT_CLK_RISE_EDGE       0x08

#define TIMER_COM_OFF       0x00
#define TIMER_COM_TGL       0x20
#define TIMER_COM_CLR       0x40
#define TIMER_COM_SET       0x80


#define TICKS_NS(time) ((F_CPU * 1ULL * (time) / 1000000000ULL) -1)
#define TICKS_US(time) ((F_CPU * 1ULL * (time) / 1000000ULL)    -1)
#define TICKS_MS(time) ((F_CPU * 1ULL * (time) / 1000ULL)       -1)
#define TICKS_S(time)  ((F_CPU * 1ULL * (time) / 1ULL)          -1)

#define TIME_NS(ticks) ((ticks+1) * 1000000000ULL / F_CPU )
#define TIME_US(ticks) ((ticks+1) * 1000000ULL    / F_CPU )
#define TIME_MS(ticks) ((ticks+1) * 1000ULL       / F_CPU )
#define TIME_S(ticks)  ((ticks+1) * 1ULL          / F_CPU )

#ifndef _INLINE_
#define _INLINE_ static inline __attribute__((always_inline))
#endif /* _INLINE_ */

_INLINE_ void Timer_Init (u8 timer, u8 mode, u32 ticks);
_INLINE_ void Timer_Start(u8 timer);
_INLINE_ void Timer_Reset(u8 timer);
_INLINE_ void Timer_Stop (u8 timer);
_INLINE_ u32  Timer_Count(u8 timer);
_INLINE_ void Timer_SetDc(u8 timer, u8 duty_cycle);
_INLINE_ void Timer_SetTime    (u8 timer, u32 ticks);
_INLINE_ void Timer_SetCmpMatch(u8 timer, u32 ticks);
_INLINE_ void Timer_CbOverflow(u8 timer, void(*callback)(void) );
_INLINE_ void Timer_CbCmpMatch(u8 timer, void(*callback)(void) );
_INLINE_ void Timer_CbCapture (u8 timer, void(*callback)(void) );
_INLINE_ u8   Timer_IsOverflow(u8 timer);
_INLINE_ u8   Timer_IsCmpMatch(u8 timer);
_INLINE_ u8   Timer_IsCaptrue (u8 timer);

void Timer0_Init(u8 mode, u32 ticks);
void Timer0_Start(void);
void Timer0_Reset(void);
void Timer0_Stop(void);
u32  Timer0_Count(void);
void Timer0_SetDc(u8 duty_cycle);
void Timer0_SetTime(u32 ticks);
void Timer0_SetCmpMatch(u32 ticks);
void Timer0_CbOverflow(void(*callback)(void) );
void Timer0_CbCmpMatch(void(*callback)(void) );
u8   Timer0_IsOverflow(void);
u8   Timer0_IsCmpMatch(void);

void Timer1_Init(u8 mode, u32 ticks);
void Timer1_Start(void);
void Timer1_Reset(void);
void Timer1_Stop(void);
u32  Timer1_Count(void);
void Timer1_SetDc(u8 duty_cycle);
void Timer1_SetTime(u32 ticks);
void Timer1_SetCmpMatch(u32 ticks);
void Timer1_CbOverflow(void(*callback)(void) );
void Timer1_CbCmpMatch(void(*callback)(void) );
void Timer1_CbCapture(void(*callback)(void) );
u8   Timer1_IsOverflow(void);
u8   Timer1_IsCmpMatch(void);
u8   Timer1_IsCapture (void);

void Timer2_Init(u8 mode, u32 ticks);
void Timer2_Start(void);
void Timer2_Reset(void);
void Timer2_Stop(void);
u32  Timer2_Count(void);
void Timer2_SetDc(u8 duty_cycle);
void Timer2_SetTime(u32 ticks);
void Timer2_SetCmpMatch(u32 ticks);
void Timer2_CbOverflow(void(*callback)(void) );
void Timer2_CbCmpMatch(void(*callback)(void) );
u8   Timer2_IsOverflow(void);
u8   Timer2_IsCmpMatch(void);

void Timer3_Init(u8 mode, u32 ticks);
void Timer3_Start(void);
void Timer3_Reset(void);
void Timer3_Stop(void);
u32  Timer3_Count(void);
void Timer3_SetDc(u8 duty_cycle);
void Timer3_SetTime(u32 ticks);
void Timer3_SetCmpMatch(u32 ticks);
void Timer3_CbOverflow(void(*callback)(void) );
void Timer3_CbCmpMatch(void(*callback)(void) );
void Timer3_CbCapture(void(*callback)(void) );
u8   Timer3_IsOverflow(void);
u8   Timer3_IsCmpMatch(void);
u8   Timer3_IsCapture (void);

_INLINE_ void Timer_Init(u8 timer, u8 mode, u32 ticks)
{
    switch(timer)
    {
        case PERIPHERAL_TIMER_0: {return Timer0_Init(mode,ticks); break;}
        case PERIPHERAL_TIMER_1: {return Timer1_Init(mode,ticks); break;}
        case PERIPHERAL_TIMER_2: {return Timer2_Init(mode,ticks); break;}
        case PERIPHERAL_TIMER_3: {return Timer3_Init(mode,ticks); break;}
        default                : {return                        ; break;}
    }
}
_INLINE_ void Timer_Start(u8 timer)
{
    switch(timer)
    {
        case PERIPHERAL_TIMER_0: {return Timer0_Start(); break;}
        case PERIPHERAL_TIMER_1: {return Timer1_Start(); break;}
        case PERIPHERAL_TIMER_2: {return Timer2_Start(); break;}
        case PERIPHERAL_TIMER_3: {return Timer3_Start(); break;}
        default                : {return               ; break;}
    }
}
_INLINE_ void Timer_Reset(u8 timer)
{
    switch(timer)
    {
        case PERIPHERAL_TIMER_0: {return Timer0_Reset(); break;}
        case PERIPHERAL_TIMER_1: {return Timer1_Reset(); break;}
        case PERIPHERAL_TIMER_2: {return Timer2_Reset(); break;}
        case PERIPHERAL_TIMER_3: {return Timer3_Reset(); break;}
        default                : {return               ; break;}
    }

}
_INLINE_ void Timer_Stop(u8 timer)
{
    switch(timer)
    {
        case PERIPHERAL_TIMER_0: {return Timer0_Stop(); break;}
        case PERIPHERAL_TIMER_1: {return Timer1_Stop(); break;}
        case PERIPHERAL_TIMER_2: {return Timer2_Stop(); break;}
        case PERIPHERAL_TIMER_3: {return Timer3_Stop(); break;}
        default                : {return              ; break;}
    }

}
_INLINE_ u32  Timer_Count(u8 timer)
{
    switch(timer)
    {
        case PERIPHERAL_TIMER_0: {return Timer0_Count(); break;}
        case PERIPHERAL_TIMER_1: {return Timer1_Count(); break;}
        case PERIPHERAL_TIMER_2: {return Timer2_Count(); break;}
        case PERIPHERAL_TIMER_3: {return Timer3_Count(); break;}
        default                : {return 0             ; break;}
    }

}
_INLINE_ void Timer_SetDc(u8 timer, u8 duty_cycle)
{
    switch(timer)
    {
        case PERIPHERAL_TIMER_0: {return Timer0_SetDc(duty_cycle); break;}
        case PERIPHERAL_TIMER_1: {return Timer1_SetDc(duty_cycle); break;}
        case PERIPHERAL_TIMER_2: {return Timer2_SetDc(duty_cycle); break;}
        case PERIPHERAL_TIMER_3: {return Timer3_SetDc(duty_cycle); break;}
        default                : {return                         ; break;}
    }

}
_INLINE_ void Timer_SetTime(u8 timer, u32 ticks)
{
    switch(timer)
    {
        case PERIPHERAL_TIMER_0: {return Timer0_SetTime(ticks); break;}
        case PERIPHERAL_TIMER_1: {return Timer1_SetTime(ticks); break;}
        case PERIPHERAL_TIMER_2: {return Timer2_SetTime(ticks); break;}
        case PERIPHERAL_TIMER_3: {return Timer3_SetTime(ticks); break;}
        default                : {return                      ; break;}
    }

}
_INLINE_ void Timer_SetCmpMatch(u8 timer, u32 ticks)
{
    switch(timer)
    {
        case PERIPHERAL_TIMER_0: {return Timer0_SetCmpMatch(ticks); break;}
        case PERIPHERAL_TIMER_1: {return Timer1_SetCmpMatch(ticks); break;}
        case PERIPHERAL_TIMER_2: {return Timer2_SetCmpMatch(ticks); break;}
        case PERIPHERAL_TIMER_3: {return Timer3_SetCmpMatch(ticks); break;}
        default                : {return                          ; break;}
    }

}
_INLINE_ void Timer_CbOverflow(u8 timer, void(*callback)(void) )
{
    switch(timer)
    {
        case PERIPHERAL_TIMER_0: {return Timer0_CbOverflow(callback); break;}
        case PERIPHERAL_TIMER_1: {return Timer1_CbOverflow(callback); break;}
        case PERIPHERAL_TIMER_2: {return Timer2_CbOverflow(callback); break;}
        case PERIPHERAL_TIMER_3: {return Timer3_CbOverflow(callback); break;}
        default                : {return            	            ; break;}
    }

}
_INLINE_ void Timer_CbCmpMatch(u8 timer, void(*callback)(void) )
{
    switch(timer)
    {
        case PERIPHERAL_TIMER_0: {return Timer0_CbCmpMatch(callback); break;}
        case PERIPHERAL_TIMER_1: {return Timer1_CbCmpMatch(callback); break;}
        case PERIPHERAL_TIMER_2: {return Timer2_CbCmpMatch(callback); break;}
        case PERIPHERAL_TIMER_3: {return Timer3_CbCmpMatch(callback); break;}
        default                : {return      		                ; break;}
    }

}
_INLINE_ void Timer_CbCapture(u8 timer, void(*callback)(void) )
{
    switch(timer)
    {
        case PERIPHERAL_TIMER_0: {return                           ; break;}
        case PERIPHERAL_TIMER_1: {return Timer1_CbCapture(callback); break;}
        case PERIPHERAL_TIMER_2: {return                           ; break;}
        case PERIPHERAL_TIMER_3: {return Timer3_CbCapture(callback); break;}
        default                : {return      		               ; break;}
    }

}
_INLINE_ u8   Timer_IsOverflow(u8 timer)
{
    switch(timer)
    {
        case PERIPHERAL_TIMER_0: {return Timer0_IsOverflow(); break;}
        case PERIPHERAL_TIMER_1: {return Timer1_IsOverflow(); break;}
        case PERIPHERAL_TIMER_2: {return Timer2_IsOverflow(); break;}
        case PERIPHERAL_TIMER_3: {return Timer3_IsOverflow(); break;}
        default                : {return 0      	        ; break;}
    }

}
_INLINE_ u8   Timer_IsCmpMatch(u8 timer)
{
    switch(timer)
    {
        case PERIPHERAL_TIMER_0: {return Timer0_IsCmpMatch(); break;}
        case PERIPHERAL_TIMER_1: {return Timer1_IsCmpMatch(); break;}
        case PERIPHERAL_TIMER_2: {return Timer2_IsCmpMatch(); break;}
        case PERIPHERAL_TIMER_3: {return Timer3_IsCmpMatch(); break;}
        default                : {return 0      	        ; break;}
    }

}
_INLINE_ u8   Timer_IsCaptrue(u8 timer)
{
    switch(timer)
    {
        case PERIPHERAL_TIMER_0: {return 0                 ; break;}
        case PERIPHERAL_TIMER_1: {return Timer1_IsCapture(); break;}
        case PERIPHERAL_TIMER_2: {return 0                 ; break;}
        case PERIPHERAL_TIMER_3: {return Timer3_IsCapture(); break;}
        default                : {return 0      	       ; break;}
    }

}

#endif
