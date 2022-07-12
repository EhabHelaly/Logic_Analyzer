#ifndef DIGITAL_SIGNAL_H
#define DIGITAL_SIGNAL_H

#include <QVector>
#include <qcustomplot.h>
#include "logic_analyzer_signal.h"

class DigitalSignal
{
public:
   DigitalSignal();
   /* process the signal */
   void analyze(double tStart, double tEnd);
   void decodeI2C(double tStart, double tEnd);
   void decodeSPI(double tStart, double tEnd);
   void decodeNEC(double tStart, double tEnd);

   QSharedPointer<QCPGraphDataContainer> data;  /* pointer to signal data */
   QSharedPointer<QCPGraphDataContainer> clk;   /* pointer to clock data used for decoding signal */
   QVector<I2cFrame> i2cMessages;
   QVector<SpiFrame> spiMessages;
   QVector<NecFrame> necMessages;

   double edgeTime   = 0;       /* Signal Sampling Time */
   double time_start = 0;       /* Sample Start Time */
   double time_end   = 0;       /* Sample End Time */
   double time_high  = 0;       /* Sample High Time */
   double time_low   = 0;       /* Sample Low Time */
   double time_max   = 0;       /* Sample Max Pulse Width */
   double time_min   = 0;       /* Sample Min Pulse Width */
   double freq_max   = 0;       /* Max Freq */
   double freq_min   = 0;       /* Min Freq */
   double freq_avg   = 0;       /* Avg Freq */
   double duty_cycle = 0;       /* Duty Cycle */
   double waves      = 0;       /* Number of complete waves */
   uint64_t pulses   = 0;       /* Number of Level change pulses */

private:
   inline double _getWidth(int index);
};

#endif /* DIGITAL_SIGNAL_H */
