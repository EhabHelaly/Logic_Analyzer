#include <avr/io.h>
#include <avr/interrupt.h>
#include "adc.h"

#define ADC_MUX_MASK        (   BM(MUX0) |  \
                                BM(MUX1) |  \
                                BM(MUX2) |  \
                                BM(MUX3) |  \
                                BM(MUX4) )

#define ADC_VREF_MASK       (0x03)

static void (*_Adc0_ISR)(u16 data);

ISR(ADC_vect)
{
    _Adc0_ISR( ADCL | (ADCH<<8) );
}
void Adc0_Init(u8 mode)
{
    /* Set Voltage Reference */
    PUT(ADMUX, BM(REFS1) | BM(REFS0) , (mode&ADC_VREF_MASK)<<REFS0  );  /* Least 2 bits in mode defines CLK divisor selection */
    /* Set CLK divisor*/
    PUT(ADCSRA, BM(ADPS2) | BM(ADPS1) | BM(ADPS0) , mode>>4); /* high nibble in mode defines CLK divisor selection */
    /* ADC enable */
    SET(ADCSRA , BM(ADEN) );
    /* Set Conversion Mode */
    if( ALL_SET(mode, ADC_MODE_FREE_RUNNING ) )
    {
        SET(ADCSRA, BM(ADFR) ); /* Enable Free Running Mode */
        SET(ADCSRA, BM(ADSC) ); /* Start Conversion */
    }
    else
    {
        CLR(ADCSRA, BM(ADFR) );  /* Enable Single Conversion Mode */
    }
}
void Adc0_SetChannel(u8 channel)
{
    /* Set ADC CHANNEL */
    PUT(ADMUX, ADC_MUX_MASK, channel);
}
void Adc0_CbConvComp(void (*callback)(u16 data) )
{
    CLR(ADCSRA, BM(ADIE) );     /* Disable ADC Interrupt */
    _Adc0_ISR = callback ;      /* Set ADC Interrupt Callback */
    if(callback)
    {
        SET(ADCSRA, BM(ADIE) ); /* Enable ADC Interrupt */
        sei();                  /* Enable Global Interrupt */
    }
}
u16  Adc0_Read(void)
{
    u16 adc_value = 0;
    if ( ALL_CLR(ADCSRA , BM(ADFR) ) ) /* Check if ADC mode is Single Conversion Mode */
    {
        SET(ADCSRA , BM(ADSC) );                /* Start Conversion */
        while ( ALL_SET( ADCSRA, BM(ADSC) ) );  /* Wait until Conversion Completes */
    }
    adc_value = ADC;
    return  adc_value;
}
