#ifndef LOGIC_ANALYZER_SIGNAL_H
#define LOGIC_ANALYZER_SIGNAL_H

#include <cstdint>
#include <vector>

/* a pulse is denoted by 2 successive points with the same logic level despite that level */
#define PULSE_NUM_POINTS 2
/* a wave is denoted by 2 successive (logic 0) points and 2 successive (logic 1) points despite their order */
#define WAVE_NUM_POINTS  (PULSE_NUM_POINTS * 2)

/* Logic High is represented by a whole number Ex: 1.0 2.0 3.0 ... */
#define IS_SIGNAL_HIGH(s) ( (s) == ( (int)(s) ) )
/* Logic Low is represented by a decimal number Ex: 0.5 1.5 2.5 ... */
#define IS_SIGNAL_LOW(s)  ( (s) != ( (int)(s) ) )


/* Boolean expression that compares signal width to reference width with tolerance from 0.0 to 1.0 */
#define CMP_SIGNAL(signal, reference, tolerance) (  ( ( (reference) * (1 - (tolerance) ) ) <= (signal) ) \
                                                 && ( (signal) <= ( (reference) * (1 + (tolerance) ) ) ) )


/** I2C protocol **/
#define I2C_DATA_FIELD_BITS   8
#define I2C_ACK_FIELD_BITS    1
#define I2C_FIELD_BITS        9                                 /* 8 data + 1 ack = 9 */

/** SPI protocol **/
#define SPI_FRAME_NUM_POINTS  30                                /* 7.5 waves = 7.5*4 = 30 points */
#define SPI_TOLERANCE         0.35                              /* not a Standard */

/** NEC protocol **/
#define NEC_START_LOW         9.0                               /* Milli seconds */
#define NEC_START_HIGH        4.5                               /* Milli seconds */
#define NEC_BIT_LOW           0.5625                            /* Milli seconds */
#define NEC_BIT_HIGH_0        NEC_BIT_LOW
#define NEC_BIT_HIGH_1        1.6875                            /* Milli seconds */
#define NEC_BIT_LOGIC_0       (NEC_BIT_LOW + NEC_BIT_HIGH_0)    /* 1.1250 Milli seconds */
#define NEC_BIT_LOGIC_1       (NEC_BIT_LOW + NEC_BIT_HIGH_1)    /* 2.2500 Milli seconds */
#define NEC_INTERFRAME_SPACE  108.0                             /* Milli seconds */
#define NEC_REPEAT_START_LOW  NEC_START_LOW
#define NEC_REPEAT_START_HIGH 2.25                              /* Milli seconds */
#define NEC_FRAME_PULSES      33
#define NEC_FRAME_BITS        32
#define NEC_TOLERANCE         0.35                              /* not a Standard */

/** NECx2 protocol **/
#define NECX2_START_LOW       NEC_START_HIGH

struct I2cField
{
   uint8_t data = 0;
   bool    ack  = false; /* denotes whether this byte is acknowledged by receiver or not acknowledged  */
};

struct I2cFrame
{
   double   time = 0;
   I2cField address;              /* data -> 7 bit address + R/W bit , ack -> denotes whether slave replied with
                                     acknowledgment or no */
   std::vector<I2cField> dataBytes;
};

struct SpiFrame
{
   double  time = 0;
   uint8_t data = 0;
};

struct NecFrame
{
   double   time    = 0;
   uint16_t address = 0;
   uint8_t  data    = 0;
   uint16_t repeat  = 0;
};

#endif /* LOGIC_ANALYZER_SIGNAL_H */
