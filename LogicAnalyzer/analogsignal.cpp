#include "analogsignal.h"
#include <iostream>
#include <string>

static bool _getSampleIndices(QSharedPointer<QCPGraphDataContainer> sample, double tStart, double tEnd, int &aStart, int &aEnd);

AnalogSignal::AnalogSignal()
{

}
void AnalogSignal::analyze(double tStart, double tEnd)
{
    int aStart=0;
    int aEnd=0;
    if(!_getSampleIndices(data,tStart, tEnd, aStart, aEnd))
    {
        AnalogSignal temp;
        temp.data       = data;
        temp.edgeTime   = edgeTime;
        temp.binary     = binary;
        *this= temp;
        return;
    }

    std::pair<QCPGraphData*,QCPGraphData*> data_min_max = std::minmax_element(data->begin(), data->end(), [](QCPGraphData const & s1, QCPGraphData const & s2) { return s1.value< s2.value; });
    /* min amp with time */
    amp_min = *data_min_max.first;
    /* max amp with time */
    amp_max = *data_min_max.second;
    /* avg amp or offset */
    offset = std::accumulate(data->begin(), data->end(), 0.0, [](double sum, QCPGraphData const & s) { return sum+s.value; }) / (double)data->size();
    /* max rate of change */
    delta_max = *std::max_element(data->begin(), data->end()-1, [](QCPGraphData const & s1, QCPGraphData const & s2) { return std::abs( ((&s1)+1)->value-s1.value) < std::abs(((&s2)+1)->value-s2.value); });
    delta_max.value /= edgeTime;
    /* */
    binary.analyze(tStart,tEnd);
}

static bool _getSampleIndices(QSharedPointer<QCPGraphDataContainer> sample, double tStart, double tEnd, int &aStart, int &aEnd)
{
    if (!sample || sample->isEmpty() || tStart>=tEnd)
    {
        return false;
    }

    aStart = 0;
    aEnd   = sample->size();
    while(aStart<sample->size() && sample->at(aStart)->key <= tStart)
    {
        aStart+=2;
    }
    while(aEnd>0 && sample->at(aEnd-1)->key >= tEnd)
    {
        aEnd-=2;
    }
    if (aStart>=aEnd)
    {
        return false;
    }
    return true;
}
