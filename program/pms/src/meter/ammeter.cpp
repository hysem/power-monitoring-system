#include "ammeter.h"
#include <math.h>

Ammeter::Ammeter(int _inputPin, int _samples, int _interval, float _offset, float referenceVoltage, float sensitivity)
{
    multiplier = referenceVoltage / (sensitivity * 1023);
    inputPin = _inputPin;
    samples = _samples;
    interval = _interval;
    offset = _offset;
}

float Ammeter::currentInst()
{
    iInst = (multiplier * analogRead(inputPin)) + offset;
    return iInst;
}

float Ammeter::current()
{
    iMax = 0;
    iMin = 1024;
    int iSample = 0;
    for (i = 0; i < samples; i++)
    {
        iSample = analogRead(inputPin);

        if (iSample > iMax)
        {
            iMax = iSample;
        }
        if (iSample < iMin)
        {
            iMin = iSample;
        }

        delay(interval);
    }
    float peakVoltage = ((float)(iMax - iMin)) / 2;
    return ((multiplier * peakVoltage) + offset) / sqrt(2);
}
