#ifndef ANALOG_SIGNAL_H
#define ANALOG_SIGNAL_H

#include <QVector>
#include <qcustomplot.h>
#include "logic_analyzer_signal.h"
#include "digitalsignal.h"

class AnalogSignal
{
public:
   AnalogSignal();
   /* process the signal */
   void analyze(double tStart, double tEnd);

   QSharedPointer<QCPGraphDataContainer> data;  /* pointer to signal data */
   DigitalSignal binary;                        /* convert analog to digital using schmitt trigger */
   double edgeTime = 0;                         /* Signal Sampling Time */
   double offset   = 0;
   QCPGraphData amp_min;
   QCPGraphData amp_max;
   QCPGraphData delta_max;
};

#endif /* ANALOG_SIGNAL_H */
