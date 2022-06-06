#include "voltmeter.h"

Voltmeter::Voltmeter(int _inputPin, int _samples, int _interval, float _offset, float referenceVoltage, float primaryVoltage, float resistorSmall, float resistorLarge)
{
    // multiplication factor = (primaryVoltage / secondaryVoltage) * ((secondaryVoltage * resistorSmall) / (resistorSmall+resistorLarge)) * sqrt(2)
    // since secondaryVoltage cancels out this will be equivalent to
    //  multiplication factor = (primaryVoltage* resistorSmall) / (resistorSmall+resistorLarge) * sqrt(2)
    multiplier = primaryVoltage * resistorSmall * referenceVoltage / ((resistorSmall + resistorLarge) * 1023);
    inputPin = _inputPin;
    samples = _samples;
    interval = _interval;
    offset = _offset;
}

float Voltmeter::voltageInst()
{
    vInst = (multiplier * analogRead(inputPin)) + offset;
    return vInst;
}

float Voltmeter::voltage()
{
    vMax = 0;
    for (i = 0; i < samples; i++)
    {
        voltageInst();
        if (vInst > vMax)
        {
            vMax = vInst;
        }
        delay(interval);
    }
    return vMax;
}
