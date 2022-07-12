#ifndef LOGIC_ANALYZER_CONFIG_H_INC
#define LOGIC_ANALYZER_CONFIG_H_INC

#include <timer.h>
#include <uart.h>
#include <gpio.h>
#include <adc.h>
#include <avr/interrupt.h>

/* Logic Analyzer Peripheral Configuration */
#define LA_ADC   PERIPHERAL_ADC_0         /* used for analog input display */
#define LA_UART  PERIPHERAL_UART_0        /* used for samples data streaming */
#define LA_GPIO  PERIPHERAL_GPIO_A        /* used for digital input display */
#define LA_TIMER PERIPHERAL_TIMER_0       /* used for managing sampling time */


/*	Note:
 *	some Registers are hard-coded in main.c for time optimization purposes
 *	those Registers must be edited when changing used peripherals
 */

/* ADC Peripheral */
#define LA_REG_ADC    ADC     /* ADC data register */
#define LA_REG_ADCSRA ADCSRA  /* ADC control/status register */
#define LA_BIT_ADSC   ADSC    /* ADC Start Conversion flag */
/* UART Peripheral */
#define LA_REG_UDR    UDR     /* UART data register */
#define LA_REG_UCSRA  UCSRA   /* UART control/status register */
#define LA_BIT_UDRE   UDRE    /* UART data register Empty flag */
/* GPIO Peripheral */
#define LA_REG_PIN    PINA    /* GPIO input register */
/* Timer Peripheral */
#define LA_REG_TIFR   TIFR    /* Timer flag register */
#define LA_BIT_OCF    OCF0    /* Timer Output Compare Match flag */


#endif /* LOGIC_ANALYZER_CONFIG_H_INC */
