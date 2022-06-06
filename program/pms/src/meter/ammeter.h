#ifndef AMMETER_H
#define AMMETER_H

#include <Arduino.h>

class Ammeter
{
public:
    Ammeter(int _inputPin, int _samples, int _interval, float _offset, float referenceVoltage, float sensitivity);
    float currentInst();
    float current();

private:
    int inputPin;
    float multiplier;
    float iInst;
    int iMax;
    int iMin;
    float offset;

    int samples;
    int i;
    int interval;
};

#endif