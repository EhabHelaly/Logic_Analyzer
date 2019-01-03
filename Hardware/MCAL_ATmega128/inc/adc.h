#ifndef ADC_H_INC
#define ADC_H_INC

#include "std_bit.h"
#include "peripheral.h"

#ifndef _INLINE_
#define _INLINE_ static inline __attribute__((always_inline))
#endif /* _INLINE_ */

/* ADC Voltage Reference (2 bits) */
#define ADC_VREF_AREF           0x00
#define ADC_VREF_VCC            0x01
#define ADC_VREF_2_56V          0x03
/* ADC Mode (2 bits) */
#define ADC_MODE_FREE_RUNNING   0x04
#define ADC_MODE_SINGLE         0x08
/* ADC Clock Divisor (2 bits) */
#define ADC_CLK_DIV_2           0x10
#define ADC_CLK_DIV_4           0x20
#define ADC_CLK_DIV_8           0x30
#define ADC_CLK_DIV_16          0x40
#define ADC_CLK_DIV_32          0x50
#define ADC_CLK_DIV_64          0x60
#define ADC_CLK_DIV_128         0x70

#define ADC_CHANNEL_0   0
#define ADC_CHANNEL_1   1
#define ADC_CHANNEL_2   2
#define ADC_CHANNEL_3   3
#define ADC_CHANNEL_4   4
#define ADC_CHANNEL_5   5
#define ADC_CHANNEL_6   6
#define ADC_CHANNEL_7   7

_INLINE_ void Adc_Init(u8 adc, u8 mode);
_INLINE_ void Adc_SetChannel(u8 adc, u8 channel);
_INLINE_ void Adc_CbConvComp(u8 adc, void (*conversion_completed_cb)(u16 data) );
_INLINE_ u16  Adc_Read(u8 adc);

void Adc0_Init(u8 mode);
void Adc0_SetChannel(u8 channel);
void Adc0_CbConvComp(void (*callback)(u16 data) );
u16  Adc0_Read(void);

_INLINE_ void Adc_Init(u8 adc, u8 mode)
{
    switch(adc)
    {
        case PERIPHERAL_ADC_0: {return Adc0_Init(mode); break;}
        default              : {return        		  ; break;}
    }

}
_INLINE_ void Adc_SetChannel(u8 adc, u8 channel)
{
    switch(adc)
    {
        case PERIPHERAL_ADC_0: {return Adc0_SetChannel(channel); break;}
        default              : {return        	           	   ; break;}
    }

}
_INLINE_ void Adc_CbConvComp(u8 adc, void (*callback)(u16 data) )
{
    switch(adc)
    {
        case PERIPHERAL_ADC_0: {return Adc0_CbConvComp(callback); break;}
        default              : {return                  		; break;}
    }
}
_INLINE_ u16  Adc_Read(u8 adc)
{
    switch(adc)
    {
        case PERIPHERAL_ADC_0: {return Adc0_Read(); break;}
        default              : {return 0      	  ; break;}
    }
}


#endif /* ADC_H_INC */
