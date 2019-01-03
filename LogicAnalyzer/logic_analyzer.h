#ifndef LOGIC_ANALYZER_H_INC

#define LOGIC_ANALYZER_H_INC

/* Logic Analyzer Commands */
#define LA_CMD_DIGITAL      0xFF    /*  8 pin digital,    200K sample rate at F_CPU 16M , UART baud rate 2M */
#define LA_CMD_DIGITAL_X2   0xFE    /*  4 pin digital,    400K sample rate at F_CPU 16M , UART baud rate 2M */
#define LA_CMD_ANALOG       0xFD    /* 10 bit resolution, 100K sample rate at F_CPU 16M , UART baud rate 2M */
#define LA_CMD_ANALOG_X2    0xFC    /*  8 bit resolution, 200K sample rate at F_CPU 16M , UART baud rate 2M */
#define LA_CMD_PULLUP_ON	0xFB	/*  enable Pull-up resistances */
#define LA_CMD_PULLUP_OFF	0xFA	/* disable Pull-up resistances */
#define LA_CMD_SYNC_CHECK   0xAA	/* test serial communication */
#define LA_CMD_OFF          0x00	/* stop serial data stream */

/* Logic Analyzer UART min cycles per frame */
#define LA_UART_CYCLES      80		/* it takes 80 clock cycles to send 1 byte through UART at max baud rate */

/* Logic Analyzer CLK Ticks */
#define LA_TIMER_TICKS_D    (LA_UART_CYCLES   -1)	/*  79 ticks,  5.0 usec at F_CPU 16M */
#define LA_TIMER_TICKS_D_X2 (LA_UART_CYCLES/2 -1)	/*  39 ticks,  2.5 usec at F_CPU 16M */
#define LA_TIMER_TICKS_A	(LA_UART_CYCLES*2 -1)	/* 159 ticks, 10.0 usec at F_CPU 16M */
#define LA_TIMER_TICKS_A_X2 (LA_UART_CYCLES   -1)	/*  79 ticks,  5.0 usec at F_CPU 16M */

#endif /* LOGIC_ANALYZER_H_INC */
