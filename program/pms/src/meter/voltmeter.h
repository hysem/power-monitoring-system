#ifndef VOLTMETER_H
#define VOLTMETER_H

#include <Arduino.h>

class Voltmeter
{
public:
    Voltmeter(int _inputPin, int _samples, int _interval, float _offset, float referenceVoltage, float primaryVoltage, float resistorSmall, float resistorLarge);
    float voltage();
    float voltageInst();

private:
    int inputPin;
    float multiplier;
    float vInst;
    float vMax;
    float offset;

    int samples;
    int i;
    int interval;
};

#endif