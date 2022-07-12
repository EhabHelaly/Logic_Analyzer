#include "digitalsignal.h"
#include <iostream>
#include <string>

#define TIME(index)      (data->at(index)->key)
#define VALUE(index)     (data->at(index)->value)
#define CLK_TIME(index)  (clk->at(index)->key)
#define CLK_VALUE(index) (clk->at(index)->value)

static bool _getSampleIndices
(
   QSharedPointer<QCPGraphDataContainer> sample,
   double                                tStart,
   double                                tEnd,
   int                                  &aStart,
   int                                  &aEnd
);

static bool _getSampleIndices
(
   QSharedPointer<QCPGraphDataContainer> sample,
   double                                tStart,
   double                                tEnd,
   int                                  &aStart,
   int                                  &aEnd
)
{
   if (  !sample
      || sample->isEmpty()
      || (tStart >= tEnd) )
   {
      return(false);
   }

   aStart = 0;
   aEnd   = sample->size();
   while (  (aStart < sample->size() )
         && (sample->at(aStart)->key <= tStart) )
   {
      aStart += 2;
   }
   while (  (aEnd > 0)
         && (sample->at(aEnd - 1)->key >= tEnd) )
   {
      aEnd -= 2;
   }

   return(aStart < aEnd);
}

/*
 * Digital Signal
 */
DigitalSignal::DigitalSignal()
{
}

inline double DigitalSignal::_getWidth(int index)
{
   return(TIME(index + 1) - TIME(index) + edgeTime);
}

void DigitalSignal::analyze(double tStart, double tEnd)
{
   int aStart = 0;
   int aEnd   = 0;


   if (!_getSampleIndices(data, tStart, tEnd, aStart, aEnd) )
   {
      DigitalSignal temp;
      temp.data     = data;
      temp.clk      = clk;
      temp.edgeTime = edgeTime;
      *this         = temp;
      return;
   }

   pulses     = (aEnd - aStart) / 2;                    /* Number of Level change pulses */
   waves      = pulses / 2.0;                           /* Number of complete waves */
   time_start = TIME(aStart);                           /* Sample Start Time */
   time_end   = TIME(aEnd - 1);                         /* Sample End Time */
   duty_cycle = 100.0;                                  /* Duty Cycle */
   time_min   = 999999999.9;                            /* 1 Billion msec */
   time_max   = 0.0;                                    /* 0 msec */
   time_high  = 0.0;                                    /* Sample High Time */
   time_low   = 0.0;                                    /* Sample Low Time */
   freq_max   = 0.0;                                    /* Max Freq */
   freq_min   = 0.0;                                    /* Min Freq */
   freq_avg   = waves / (time_end - time_start) * 1000; /* Avr Freq */

   for (int a = aStart; a < aEnd; a += 2)
   {
      double dt = _getWidth(a);

      if (IS_SIGNAL_HIGH(VALUE(a) ) )
      {
         time_high += dt;
      }
      else
      {
         time_low += dt;
      }

      if (dt < time_min)
      {
         time_min = dt;
      }
      if (dt > time_max)
      {
         time_max = dt;
      }
   }

   duty_cycle = 100 * time_high / (time_high + time_low);
   freq_max   = 1000 / (time_min * 2);
   freq_min   = 1000 / (time_max * 2);
}

/* I2C decoding algorithm
 * 1: find start condition
 *      - loop on SDA line low (logic 0) pulses
 *      - check if SCL is high (logic 1) at each pulse
 * 2: find repeated start or stop condition
 *      - loop on SDA line next pulses (both high and low)
 *      - check if SCL is high (logic 1) at each pulse
 * 3: ensure that a valid number of SCL clock cycles is found between conditions
 *      - number of cycles must be multiples of 9 (8 data bits+1 ack)
 * 4: decode slave address and tranceived data
 *      - read value on SDA line corresponding to start of each High (logic 1) pulses on SCL line
 * 5: repeat algorithm ( starting by the repeated start or after the stop condtion )
 */

void DigitalSignal::decodeI2C(double tStart, double tEnd)
{
   int aStart = 0;
   int aEnd   = 0;


   i2cMessages.clear();
   if (!_getSampleIndices(data, tStart, tEnd, aStart, aEnd) )
   {
      return;
   }

   /* get low pulse */
   if (IS_SIGNAL_HIGH(VALUE(aStart) ) )
   {
      aStart += PULSE_NUM_POINTS;
   }
   aEnd += PULSE_NUM_POINTS;

   int a = aStart;


   while (a < aEnd)
   {
      const QCPGraphData *i2c_start = clk->findBegin(TIME(a), false);
      const QCPGraphData *i2c_repeatedStart_or_stop;

      if (IS_SIGNAL_HIGH(i2c_start->value) ) /* a valid start condition is found ? */
      {
         int b = a + PULSE_NUM_POINTS;       /* move to next pulse */
         do
         {
            i2c_repeatedStart_or_stop = clk->findBegin(TIME(b), false); /* get SCL point at this SDA time */
         }while
         (
            /* loop until SDA line changes while SCL is High or until signal ends */
            (  IS_SIGNAL_LOW(i2c_repeatedStart_or_stop->value)          /* look for high pulse in CLK */
            || IS_SIGNAL_LOW( (i2c_repeatedStart_or_stop - 1)->value) ) /* look for high pulse in CLK */
         && ( (b += PULSE_NUM_POINTS) < aEnd)                           /* move to next pulse */
         );

         if (IS_SIGNAL_HIGH(i2c_repeatedStart_or_stop->value) )         /* stop/repeated start condition is found? */
         {
            uint32_t i2c_bits = i2c_repeatedStart_or_stop - i2c_start;
            i2c_bits = i2c_bits / WAVE_NUM_POINTS - 1;
            /* a valid number of clk cycles between start and stop ? */
            if (  (i2c_bits >= I2C_FIELD_BITS)
               && (i2c_bits % I2C_FIELD_BITS == 0) )
            {
               I2cFrame            frame;
               const QCPGraphData *clk_tick  = i2c_start + PULSE_NUM_POINTS + 1; /* start point of next high pulse */
               uint16_t            i2c_field = 0;                                /* 9 bit field */

               /* get Address + R/W bit + Slave Ack */
               for (int index = 0; index < I2C_FIELD_BITS; index++) /* loops 9 times */
               {
                  i2c_field = (i2c_field << 1) | (IS_SIGNAL_HIGH(data->findBegin(clk_tick->key, false)->value) ? 1 : 0);
                  clk_tick += WAVE_NUM_POINTS;
               }
               frame.time         = TIME(a);
               frame.address.data = i2c_field >> 1;   /* 1 shift for ack */
               frame.address.ack  = (i2c_field & 0x1) == 0;

               /* get Data + Receiver (Master/Slave) Ack */
               /* loops up to number of i2c fields - 1 */
               for (uint8_t index = 1; index < i2c_bits / I2C_FIELD_BITS; index++)
               {
                  i2c_field = 0;
                  for (int index = 0; index < I2C_FIELD_BITS; index++)  /* loops 9 times */
                  {
                     i2c_field =
                        (i2c_field << 1) | (IS_SIGNAL_HIGH(data->findBegin(clk_tick->key, false)->value) ? 1 : 0);
                     clk_tick += WAVE_NUM_POINTS;
                  }
                  I2cField frame_field;
                  frame_field.data = i2c_field >> 1;    /* 1 shift for ack */
                  frame_field.ack  = (i2c_field & 0x1) == 0;
                  frame.dataBytes.push_back(frame_field);
               }
               i2cMessages.push_back(frame);

            }
            if (IS_SIGNAL_HIGH(VALUE(b) ) ) /* stop condition ? */
            {
               a = b + PULSE_NUM_POINTS;    /* move to next low pulse */
            }
            else                            /* repeated start condition */
            {
               a = b;                       /* move to repeated start */
            }

         }
         else /* not a single valid stop condition was found till the end of signal */
         {
            a = aEnd; /* move to signal end */
         }
      }
      else /* this point is not a valid start condition */
      {
         a += WAVE_NUM_POINTS;  /* move to next low pulse */
      }
   }
}
void DigitalSignal::decodeSPI(double tStart, double tEnd)
{
   int aStart = 0;
   int aEnd   = 0;


   spiMessages.clear();
   if (!_getSampleIndices(clk, tStart, tEnd, aStart, aEnd) )
   {
      return;
   }

   /* sampling on falling edge */
   if (IS_SIGNAL_LOW(CLK_VALUE(aStart) ) )
   {
      aStart += 2;
   }

   int a = aStart;


   while (a <= (aEnd - SPI_FRAME_NUM_POINTS) )
   {
      bool error_in_frame = false;

      double              wave_width = clk->at(a + WAVE_NUM_POINTS)->key - clk->at(a)->key + edgeTime;
      const QCPGraphData *found      = data->findBegin(CLK_TIME(a + 1) );
      uint8_t             byte       = IS_SIGNAL_HIGH(found->value) ? 1 : 0; /* MSB first */
      /* get low pulse */
      a += PULSE_NUM_POINTS;
      for (int b = 0; b < 7 * WAVE_NUM_POINTS; b += WAVE_NUM_POINTS)
      {
         found = data->findBegin(CLK_TIME(a + b + WAVE_NUM_POINTS) );
         byte  = (byte << 1) | (IS_SIGNAL_HIGH(found->value) ? 1 : 0); /* MSB first */
         double width = clk->at(a + b + WAVE_NUM_POINTS)->key - clk->at(a + b)->key + edgeTime;
         if (!CMP_SIGNAL(width, wave_width, 0.5) )
         {
            error_in_frame = true;
            a             += b + PULSE_NUM_POINTS;
            break;
         }
      }
      if (!error_in_frame)
      {
         SpiFrame frame;
         frame.time = CLK_TIME(a);
         frame.data = byte;
         spiMessages.push_back(frame);
         a += SPI_FRAME_NUM_POINTS;
      }
   }

}
void DigitalSignal::decodeNEC(double tStart, double tEnd)
{
   int      aStart  = 0;
   int      aEnd    = 0;
   uint32_t message = 0;


   necMessages.clear();
   if (  !_getSampleIndices(data, tStart, tEnd, aStart, aEnd)
      || (waves < NEC_FRAME_PULSES) )
   {
      return;
   }

   /* get first low pulse */
   if (IS_SIGNAL_HIGH(VALUE(aStart) ) )
   {
      aStart += 2;
   }

   for (int a = aStart; a < aEnd; a += WAVE_NUM_POINTS)
   {
      if (  (a <= (aEnd - (NEC_FRAME_PULSES * WAVE_NUM_POINTS) ) ) /* a valid number of waves is left? */
         && (  CMP_SIGNAL(_getWidth(a), NEC_START_LOW, NEC_TOLERANCE)
            || CMP_SIGNAL(_getWidth(a), NECX2_START_LOW, NEC_TOLERANCE) )
         && CMP_SIGNAL(_getWidth(a + PULSE_NUM_POINTS), NEC_START_HIGH, NEC_TOLERANCE) )
      {
         bool errorFlag = false;
         for (int b = 0; b < NEC_FRAME_BITS; b++)
         {
            a += WAVE_NUM_POINTS;
            double pulse_low  = _getWidth(a);
            double pulse_high = _getWidth(a + PULSE_NUM_POINTS);
            if (  CMP_SIGNAL(pulse_low, NEC_BIT_LOW, NEC_TOLERANCE)
               && (  CMP_SIGNAL(pulse_high, NEC_BIT_HIGH_0, NEC_TOLERANCE)
                  || CMP_SIGNAL(pulse_high, NEC_BIT_HIGH_1, NEC_TOLERANCE) ) )
            {
               message = (message >> 1) | (CMP_SIGNAL(pulse_high, NEC_BIT_HIGH_1, NEC_TOLERANCE) ? (1UL << 31) : 0);
            }
            else     /* error in frame */
            {
               errorFlag = true;
               a        -= WAVE_NUM_POINTS; /* return 1 step back */
               break;
            }
         }
         if (!errorFlag)
         {
            NecFrame frame;
            uint8_t  data_inverse = 0;
            frame.address = (message >> 0) & 0xFFFF;
            frame.data    = (message >> 16) & 0xFF;
            data_inverse  = (message >> 24) & 0xFF;
            frame.time    = TIME(a - (NEC_FRAME_BITS * WAVE_NUM_POINTS) );
            frame.repeat  = 0;
            if ( (frame.data ^ data_inverse) == 0xFF)      /* check if frame data is correct */
            {
               necMessages.push_back(frame);
            }
         }
      }
      else if (  necMessages.size()
              && (a <= (aEnd - WAVE_NUM_POINTS) )      /* a valid number of waves is left? */
              && CMP_SIGNAL(_getWidth(a), NEC_REPEAT_START_LOW, NEC_TOLERANCE)
              && CMP_SIGNAL(_getWidth(a + PULSE_NUM_POINTS), NEC_REPEAT_START_HIGH, NEC_TOLERANCE)
              && CMP_SIGNAL(TIME(a) - necMessages.back().time, NEC_INTERFRAME_SPACE * (necMessages.back().repeat + 1),
                            NEC_TOLERANCE)
              )
      {
         necMessages.back().repeat++;
      }
   }

}
