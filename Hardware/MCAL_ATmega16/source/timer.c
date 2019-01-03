#ifndef F_CPU
#warning "F_CPU" is not defined, default value will be used, it is adviced to define "F_CPU" in project's compiler macros'
#define F_CPU 1000000UL
#endif // F_CPU

#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"

#define TIMER_MODE_MASK (   TIMER_MODE_NORMAL   | \
                            TIMER_MODE_CTC      | \
                            TIMER_MODE_PWM      | \
                            TIMER_MODE_FAST_PWM   )

#define TIMER_COM_MASK (    TIMER_COM_OFF    | \
                            TIMER_COM_TGL    | \
                            TIMER_COM_CLR    | \
                            TIMER_COM_SET      )

#define OC0  3
#define OC1A 5
#define OC1B 4
#define OC2  7

#define OC0_DIR_R DDRB
#define OC1_DIR_R DDRD
#define OC2_DIR_R DDRD

static void (*_Timer0_CMP_ISR)(void);
static void (*_Timer0_OVF_ISR)(void);

static void (*_Timer1_CMPA_ISR)(void);
static void (*_Timer1_CMPB_ISR)(void);
static void (*_Timer1_OVF_ISR)(void);
static void (*_Timer1_CPT_ISR)(void);

static void (*_Timer2_CMP_ISR)(void);
static void (*_Timer2_OVF_ISR)(void);

static u8 _Timer0_prsc=0;
static u8 _Timer1_prsc=0;
static u8 _Timer2_prsc=0;

ISR(TIMER0_OVF_vect)
{
	_Timer0_OVF_ISR();
}
ISR(TIMER0_COMP_vect)
{
	_Timer0_CMP_ISR();
}
ISR(TIMER1_OVF_vect)
{
	_Timer1_OVF_ISR();
}
ISR(TIMER1_COMPA_vect)
{
	_Timer1_CMPA_ISR();
}
ISR(TIMER1_COMPB_vect)
{
	_Timer1_CMPB_ISR();
}
ISR(TIMER1_CAPT_vect)
{
	_Timer1_CPT_ISR();
}
ISR(TIMER2_OVF_vect)
{
	_Timer2_OVF_ISR();
}
ISR(TIMER2_COMP_vect)
{
	_Timer2_CMP_ISR();
}

void Timer0_Init(u8 mode, u32 ticks)
{
    Timer0_Stop();
    SET(TIFR, BM(OCF0) | BM(TOV0) ); /* clear flags */

    switch(mode&TIMER_MODE_MASK) /* TIMER_MODE */
    {
        case TIMER_MODE_NORMAL  : {TCCR0 = BM(FOC0)                        ;break;}
        case TIMER_MODE_PWM     : {TCCR0 = BM(FOC0)             | BM(WGM00);break;}
        case TIMER_MODE_CTC     : {TCCR0 = BM(FOC0) | BM(WGM01)            ;break;}
        case TIMER_MODE_FAST_PWM: {TCCR0 = BM(FOC0) | BM(WGM01) | BM(WGM00);break;}
        default /*Mode Normal*/ : {TCCR0 = BM(FOC0)                        ;break;}
    }

    CLR(TCCR0, BM(COM01) | BM(COM00) );
    switch(mode&TIMER_COM_MASK) /* TIMER_COMPARE_OUTPUT_MODE */
    {
        case TIMER_COM_OFF: {                                                             break;}
        case TIMER_COM_TGL: {SET(TCCR0,             BM(COM00) ); SET(OC0_DIR_R, BM(OC0)); break;}
        case TIMER_COM_CLR: {SET(TCCR0, BM(COM01)             ); SET(OC0_DIR_R, BM(OC0)); break;}
        case TIMER_COM_SET: {SET(TCCR0, BM(COM01) | BM(COM00) ); SET(OC0_DIR_R, BM(OC0)); break;}
        default  /*OFF*/  : {                                                             break;}
    }

    Timer0_SetTime(ticks);
}
void Timer0_Start(void)
{
    CLR(TCCR0 , BM(CS02)|BM(CS01)|BM(CS00) );
    TCNT0=0;
    SET(TCCR0, _Timer0_prsc);
}
void Timer0_Reset(void)
{
    TCNT0=0;
}
void Timer0_Stop(void)
{
    CLR(TCCR0 , BM(CS02)|BM(CS01)|BM(CS00) );
}
u32 Timer0_Count(void)
{
    u32 prsc[6]={32,0,3,6,8,10};
    u32 retval= ((u32)TCNT0) << prsc[_Timer0_prsc] ;
    return retval;
}
void Timer0_SetDc(u8 duty_cycle)
{
    OCR0 = 2.55f * duty_cycle;
    if( TCNT0 > OCR0 )
    {
        TCNT0 = OCR0 - 1;
    }
}
void Timer0_SetTime(u32 ticks)
{
    /* pre-scaling */
    if      (ticks<=0xFF*   1UL)    {                                   _Timer0_prsc =                   BM(CS00); }
    else if (ticks<=0xFF*   8UL)    { ticks>>= 3; /* divide by    8*/   _Timer0_prsc =          BM(CS01)         ; }
    else if (ticks<=0xFF*  64UL)    { ticks>>= 6; /* divide by   64*/   _Timer0_prsc =          BM(CS01)|BM(CS00); }
    else if (ticks<=0xFF* 256UL)    { ticks>>= 8; /* divide by  256*/   _Timer0_prsc = BM(CS02)                  ; }
    else  /*(ticks<=0xFF*1024UL)*/  { ticks>>=10; /* divide by 1024*/   _Timer0_prsc = BM(CS02)         |BM(CS00); }

    Timer0_Stop();
    OCR0=ticks;
    SET(TCCR0, _Timer0_prsc);
}
void Timer0_SetCmpMatch(u32 ticks)
{
    Timer0_SetTime(ticks);
}
void Timer0_CbOverflow(void(*callback)(void) )
{
    CLR(TIMSK, BM(TOIE0) );
    _Timer0_OVF_ISR = callback ;
    if(callback)
    {
        SET(TIMSK, BM(TOIE0) );
        sei();
    }
}
void Timer0_CbCmpMatch(void(*callback)(void) )
{
    CLR(TIMSK, BM(OCIE0) );
    _Timer0_CMP_ISR = callback ;
    if(callback)
    {
        SET(TIMSK, BM(OCIE0) );
        sei();
    }
}
u8   Timer0_IsOverflow(void)
{
    u8 result= ALL_SET( TIFR , BM(TOV0) );
    if (result)
    {
        SET(TIFR,BM(TOV0)); /* Clear Flag */
    }
    return result;
}
u8   Timer0_IsCmpMatch(void)
{
    u8 result= ALL_SET( TIFR , BM(OCF0) );
    if (result)
    {
        SET(TIFR,BM(OCF0)); /* Clear Flag */
    }
    return result;
}
void Timer1_Init(u8 mode, u32 ticks)
{
    Timer1_Stop();
    SET(TIFR, BM(ICF1) | BM(OCF1A) | BM(OCF1B) | BM(TOV1) ); /* clear flags */

    switch(mode&0x0F) /* TIMER_MODE */
    {
        case TIMER_MODE_NORMAL  : {TCCR1A = BM(FOC1A) | BM(FOC1B)                        ; TCCR1B = 0                    ; break;}
        case TIMER_MODE_PWM     : {TCCR1A = BM(FOC1A) | BM(FOC1B) | BM(WGM11) | BM(WGM10); TCCR1B = BM(WGM13)            ; break;}
        case TIMER_MODE_CTC     : {TCCR1A = BM(FOC1A) | BM(FOC1B)                        ; TCCR1B =             BM(WGM12); break;}
        case TIMER_MODE_FAST_PWM: {TCCR1A = BM(FOC1A) | BM(FOC1B) | BM(WGM11) | BM(WGM10); TCCR1B = BM(WGM13) | BM(WGM12); break;}
        default /*Mode Normal*/ : {TCCR1A = BM(FOC1A) | BM(FOC1B)                        ; TCCR1B = 0                    ; break;}
    }

    CLR(TCCR1A, BM(COM1B1) | BM(COM1B0) | BM(COM1A1) | BM(COM1A0) );
    switch(mode&0xF0) /* TIMER_COMPARE_OUTPUT_MODE */
    {
        case TIMER_COM_OFF: {                                                                 break;}
        case TIMER_COM_TGL: {SET(TCCR1A,              BM(COM1A0) ); SET(OC1_DIR_R, BM(OC1A)); break;}
        case TIMER_COM_CLR: {SET(TCCR1A, BM(COM1A1)              ); SET(OC1_DIR_R, BM(OC1A)); break;}
        case TIMER_COM_SET: {SET(TCCR1A, BM(COM1A1) | BM(COM1A0) ); SET(OC1_DIR_R, BM(OC1A)); break;}
        default  /*OFF*/  : {                                                                 break;}
    }

    Timer1_SetTime(ticks);
}
void Timer1_Start(void)
{
    CLR(TCCR1B, BM(CS12)|BM(CS11)|BM(CS10) );
    TCNT1=0;
    SET(TCCR1B, _Timer1_prsc);
}
void Timer1_Reset(void)
{
    TCNT1=0;
}
void Timer1_Stop(void)
{
    CLR(TCCR1B, BM(CS12)|BM(CS11)|BM(CS10) );
}
u32 Timer1_Count(void)
{
    u32 prsc[6]={32,0,3,6,8,10};
    u32 retval= ((u32)TCNT1) << prsc[_Timer1_prsc] ;
    return retval;
}
u32 Timer1_Capture(void)
{
    u32 prsc[6]={32,0,3,6,8,10};
    u32 retval= ((u32)ICR1) << prsc[_Timer1_prsc] ;
    return retval;
}
void Timer1_SetDc(u8 duty_cycle)
{
    OCR1A = 2.55f * duty_cycle;
    if( TCNT1 > OCR1A )
    {
        TCNT1 = OCR1A - 1;
    }
}
void Timer1_SetTime(u32 ticks)
{
    /* pre-scaling */
    if      (ticks<=0xFFFF*   1UL)  {                                   _Timer1_prsc =                   BM(CS10); }
    else if (ticks<=0xFFFF*   8UL)  { ticks>>= 3; /* divide by    8*/   _Timer1_prsc =          BM(CS11)         ; }
    else if (ticks<=0xFFFF*  64UL)  { ticks>>= 6; /* divide by   64*/   _Timer1_prsc =          BM(CS11)|BM(CS10); }
    else if (ticks<=0xFFFF* 256UL)  { ticks>>= 8; /* divide by  256*/   _Timer1_prsc = BM(CS12)                  ; }
    else  /*(ticks<=0xFFFF*1024UL)*/{ ticks>>=10; /* divide by 1024*/   _Timer1_prsc = BM(CS12)         |BM(CS10); }

    Timer1_Stop();
    OCR1A=ticks;
    SET(TCCR1B, _Timer1_prsc);
}
void Timer1_SetCmpMatch(u32 ticks)
{
    Timer1_SetTime(ticks);
}
void Timer1_CbOverflow(void(*callback)(void) )
{
    CLR(TIMSK, BM(TOIE1) );
    _Timer1_OVF_ISR = callback ;
    if(callback)
    {
        SET(TIMSK, BM(TOIE1) );
        sei();
    }
}
void Timer1_CbCmpMatch(void(*callback)(void) )
{
    CLR(TIMSK, BM(OCIE1A) );
    _Timer1_CMPA_ISR = callback ;
    if(callback)
    {
        SET(TIMSK, BM(OCIE1A) );
        sei();
    }
}
void Timer1_CbCapture(void(*callback)(void) )
{
    CLR(TIMSK, BM(TICIE1) );
    _Timer1_CPT_ISR = callback ;
    if(callback)
    {
        SET(TIMSK, BM(TICIE1) );
        sei();
    }
}
u8   Timer1_IsOverflow(void)
{
    u8 result= ALL_SET( TIFR , BM(TOV1) );
    if (result)
    {
        SET(TIFR,BM(TOV1)); /* Clear Flag */
    }
    return result;
}
u8   Timer1_IsCmpMatch(void)
{
    u8 result= ALL_SET( TIFR , BM(OCF1A) );
    if (result)
    {
        SET(TIFR,BM(OCF1A)); /* Clear Flag */
    }
    return result;
}
u8   Timer1_IsCapture (void)
{
    u8 result= ALL_SET( TIFR , BM(ICF1) );
    if (result)
    {
        SET(TIFR,BM(ICF1)); /* Clear Flag */
    }
    return result;
}
void Timer2_Init(u8 mode, u32 ticks)
{
    Timer2_Stop();
    SET(TIFR, BM(OCF2) | BM(TOV2) ); /* clear flags */

    switch(mode&0x0F) /* TIMER_MODE */
    {
        case TIMER_MODE_NORMAL  : {TCCR2 = BM(FOC2)                        ; break;}
        case TIMER_MODE_PWM     : {TCCR2 = BM(FOC2)             | BM(WGM20); break;}
        case TIMER_MODE_CTC     : {TCCR2 = BM(FOC2) | BM(WGM21)            ; break;}
        case TIMER_MODE_FAST_PWM: {TCCR2 = BM(FOC2) | BM(WGM21) | BM(WGM20); break;}
        default /*Mode Normal*/ : {TCCR2 = BM(FOC2)                        ; break;}
    }

    CLR(TCCR2, BM(COM21) | BM(COM20) );
    switch(mode&0xF0) /* TIMER_COMPARE_OUTPUT_MODE */
    {
        case TIMER_COM_OFF: {                                                             break;}
        case TIMER_COM_TGL: {SET(TCCR2,             BM(COM20) ); SET(OC2_DIR_R, BM(OC2)); break;}
        case TIMER_COM_CLR: {SET(TCCR2, BM(COM21)             ); SET(OC2_DIR_R, BM(OC2)); break;}
        case TIMER_COM_SET: {SET(TCCR2, BM(COM21) | BM(COM20) ); SET(OC2_DIR_R, BM(OC2)); break;}
        default  /*OFF*/  : {                                                             break;}
    }

    Timer2_SetTime(ticks);
}
void Timer2_Start(void)
{
    CLR(TCCR2 , BM(CS22)|BM(CS21)|BM(CS20) );
    TCNT2=0;
    SET(TCCR2 , _Timer2_prsc);
}
void Timer2_Reset(void)
{
    TCNT2=0;
}
void Timer2_Stop(void)
{
    CLR(TCCR2 , BM(CS22)|BM(CS21)|BM(CS20) );
}
u32 Timer2_Count(void)
{
    u32 prsc[8]={32,0,3,5,6,7,8,10};
    u32 retval= ((u32)TCNT2) << prsc[_Timer2_prsc] ;
    return retval;
}
void Timer2_SetDc(u8 duty_cycle)
{
    OCR2 = 2.55f * duty_cycle;
    if( TCNT1 > OCR2 )
    {
        TCNT1 = OCR2 - 1;
    }
}
void Timer2_SetTime(u32 ticks)
{
    /* pre-scaling */
    if      (ticks<=0xFF*   1UL)    {                                   _Timer2_prsc =                   BM(CS20); }
    else if (ticks<=0xFF*   8UL)    { ticks>>= 3; /* divide by    8*/   _Timer2_prsc =          BM(CS21)         ; }
    else if (ticks<=0xFF*  32UL)    { ticks>>= 5; /* divide by   32*/   _Timer2_prsc =          BM(CS21)|BM(CS20); }
    else if (ticks<=0xFF*  64UL)    { ticks>>= 6; /* divide by   64*/   _Timer2_prsc = BM(CS22)                  ; }
    else if (ticks<=0xFF* 128UL)    { ticks>>= 7; /* divide by  128*/   _Timer2_prsc = BM(CS22)         |BM(CS20); }
    else if (ticks<=0xFF* 256UL)    { ticks>>= 8; /* divide by  256*/   _Timer2_prsc = BM(CS22)|BM(CS21)         ; }
    else  /*(ticks<=0xFF*1024UL)*/  { ticks>>=10; /* divide by 1024*/   _Timer2_prsc = BM(CS22)|BM(CS21)|BM(CS20); }

    Timer2_Stop();
    OCR2=ticks;
    SET(TCCR2, _Timer2_prsc);
}
void Timer2_SetCmpMatch(u32 ticks)
{
    Timer2_SetTime(ticks);
}
void Timer2_CbOverflow(void(*callback)(void) )
{
    CLR(TIMSK, BM(TOIE2) );
    _Timer2_OVF_ISR = callback ;
    if(callback)
    {
        SET(TIMSK, BM(TOIE2) );
        sei();
    }
}
void Timer2_CbCmpMatch(void(*callback)(void) )
{
    CLR(TIMSK, BM(OCIE2) );
    _Timer2_CMP_ISR = callback ;
    if(callback)
    {
        SET(TIMSK, BM(OCIE2) );
        sei();
    }
}
u8   Timer2_IsOverflow(void)
{
    u8 result= ALL_SET( TIFR , BM(TOV2) );
    if (result)
    {
        SET(TIFR,BM(TOV2)); /* Clear Flag */
    }
    return result;
}
u8   Timer2_IsCmpMatch(void)
{
    u8 result= ALL_SET( TIFR , BM(OCF2) );
    if (result)
    {
        SET(TIFR,BM(OCF2)); /* Clear Flag */
    }
    return result;
}

