#include "logic_analyzer.h"
#include "logic_analyzer_config.h"


static u8 boost_data             = 0;			/* contains combined digital samples used in DIGITAL_X modes */
static volatile u8 boost_counter = 0;			/* controls when to transmit combined digital samples in DIGITAL_X modes */
static volatile u8 mode          = LA_CMD_OFF;	/* contains Command received through UART Transceiver */

void receive_command(u8 cmd);					/* UART receive callback (executes received commands) */

int main(void)
{

	/* Initialize System Peripherals */
	Gpio_Init(LA_GPIO, 0xFF, GPIO_CONFIG_INPPUT|GPIO_CONFIG_PULL_UP);   /* Digital Input */
	Adc_Init(LA_ADC, ADC_VREF_VCC|ADC_MODE_SINGLE);                     /* Analog Input */
	Adc_SetChannel(LA_ADC, ADC_CHANNEL_0);                              /* Analog Input Channel */
	Timer_Init(LA_TIMER, TIMER_MODE_CTC, LA_TIMER_TICKS_D);				/* Timer Mode Clear on Compare Match */
	Timer_Stop(LA_TIMER);                                               /* Stop Timer until next data stream */
	Uart_Init(LA_UART, UART_MAX_BAUDRATE);                              /* UART Transceiver */
	Uart_CbRecv(LA_UART, receive_command);								/* UART Receiver ISR */

	/*	Note:
	*	program main loop code is not Abstract and does not use MCAL APIs for time optimization purposes,
	*	all Registers are hard-coded in this section and are defined as Macros in "logic_analyzer_config.h" , 
	*	those Macros can be modified in "logic_analyzer_config.h" when changing used peripherals
	*/
	
	/* Program Main Loop */
	while(1)
	{
		if (ALL_SET( LA_REG_TIFR , BM(LA_BIT_OCF) ))	/* check if Timer Compare Match occurred */
		{
			SET( LA_REG_TIFR , BM(LA_BIT_OCF) );		/* Clear Timer Compare Match Flag */
			switch(mode)
			{
				case LA_CMD_ANALOG:
				{
					SET( LA_REG_ADCSRA , BM(LA_BIT_ADSC) );					/* Start ADC Conversion */
					while ( ALL_SET( LA_REG_ADCSRA, BM(LA_BIT_ADSC) ) );	/* Wait until ADC Conversion Completes */
					while ( ALL_CLR( LA_REG_UCSRA , BM(LA_BIT_UDRE) ) );	/* Blocks when a previous UART transmission is not finished */
					LA_REG_UDR = LA_REG_ADC;								/* Send low byte through UART */
					while ( ALL_CLR( LA_REG_UCSRA , BM(LA_BIT_UDRE) ) );	/* Blocks when a previous UART transmission is not finished */
					LA_REG_UDR = LA_REG_ADC>>8;								/* Send high byte through UART */
					break;
				}
				case LA_CMD_ANALOG_X2:
				{
					SET( LA_REG_ADCSRA , BM(LA_BIT_ADSC) );					/* Start ADC Conversion */
					while ( ALL_SET( LA_REG_ADCSRA, BM(LA_BIT_ADSC) ) );	/* Wait until ADC Conversion Completes */
					while ( ALL_CLR( LA_REG_UCSRA , BM(LA_BIT_UDRE) ) );	/* Blocks when a previous UART transmission is not finished */
					LA_REG_UDR = LA_REG_ADC>>2 ;							/* Send byte through UART */
					break;
				}
				case LA_CMD_DIGITAL:
				{
					while ( ALL_CLR( LA_REG_UCSRA , BM(LA_BIT_UDRE) ) );	/* Blocks when a previous UART transmission is not finished */
					LA_REG_UDR = LA_REG_PIN;								/* Send byte through UART */
					break;
				}
				case LA_CMD_DIGITAL_X2:
				{
					boost_data = (boost_data<<4) | ( LA_REG_PIN&0x0F );		/* combine 2 samples (4 bits each) in 1 byte to be transmitted */
					if( (boost_counter++)& 0x01 )							/* send data though UART every 2 counts */
					{
						while ( ALL_CLR( LA_REG_UCSRA , BM(LA_BIT_UDRE) ) );/* Blocks when a previous UART transmission is not finished */
						LA_REG_UDR = boost_data;							/* Send byte through UART */
					}
					break;
				}
				case LA_CMD_OFF:
				default:
				{
					/* do nothing */
					break;
				}
			}/* end of switch case */
		}/* end of Timer Compare Match check (if condition) */
	}/* end of Program Main Loop */
	
	
	return 0;
}

void receive_command(u8 cmd)
{
	Timer_Stop(LA_TIMER);   /* Stops the timer if running to parse command */
	Timer_Reset(LA_TIMER);  /* Reset the timer for next data stream */
	boost_counter=0;        /* Reset Counter for the next data stream */
	switch(cmd)
	{
		case LA_CMD_ANALOG:
		{
			mode = LA_CMD_ANALOG;
			/* Starts timer with 100K Sample Rate */
			Timer_SetCmpMatch(LA_TIMER, LA_TIMER_TICKS_A);
			break;
		}
		case LA_CMD_ANALOG_X2:
		case LA_CMD_DIGITAL:
		{
			mode = cmd;
			/* Starts timer with 200K Sample Rate*/
			Timer_SetCmpMatch(LA_TIMER, LA_TIMER_TICKS_D);
			break;
		}
		case LA_CMD_DIGITAL_X2:
		{
			mode = LA_CMD_DIGITAL_X2;
			/* Starts timer with 400K Sample Rate*/
			Timer_SetCmpMatch(LA_TIMER, LA_TIMER_TICKS_D_X2);
			break;
		}
		case LA_CMD_SYNC_CHECK:
		{
			/* reply with sync byte to ensure baud rate match */
			Uart_PutC(LA_UART, LA_CMD_SYNC_CHECK);
			break;
		}
		case LA_CMD_PULLUP_ON:
		{
			/* enable Pull-up resistances on digital input */
			Gpio_Init(LA_GPIO, 0xFF, GPIO_CONFIG_INPPUT|GPIO_CONFIG_PULL_UP);
			break;
		}
		case LA_CMD_PULLUP_OFF:
		{
			/* disable Pull-up resistances on digital input */
			Gpio_Init(LA_GPIO, 0xFF, GPIO_CONFIG_INPPUT|GPIO_CONFIG_NO_PULL);
			break;
		}
		case LA_CMD_OFF:
		default:
		{
			mode = LA_CMD_OFF;
			/* Timer is already stopped */
			break;
		}
	}
}
