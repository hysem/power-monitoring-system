#ifndef PFMETER_H
#define PFMETER_H

#include <Arduino.h>

class PFMeter
{
public:
    PFMeter(int _voltageInputPin, int _currentInputPin, int _samples, int _interval);
    float powerFactor();

private:
    int voltageInputPin;
    int currentInputPin;
    int samples;
    int interval;
    int i;

    // return ((float)randnum(80, 90)) / (float)(100);
    int expectedFrequency;
    float voltageAnalogOffset;
    float currentAnalogOffset;
    unsigned long startMicrosPA;
    unsigned long vCurrentMicrosPA;
    unsigned long iCurrentMicrosPA;
    unsigned long periodMicrosPA;
    float vAnalogValue;
    float iAnalogValue;
    float previousValueV;
    float previousValueI;
    float previousphaseAngleSample;
    float phaseAngleSample;
    float phaseAngleAccumulate;
    float periodSample;
    float periodSampleAccumulate;
    float phaseDifference;
    float phaseAngle;
    float frequency;
    float voltagePhaseAngle;
    float currentPhaseAngle;
    float averagePeriod;
    int sampleCount;
    int a = 3;
    float pf;

    // 1.1 - Phase Angle Offset

    float currentOffsetRead;
    float currentOffsetLastSample;
    float currentOffsetSampleCount;
    float voltageOffsetRead;
    float voltageOffsetLastSample;
    float voltageOffsetSampleCount;
};

#endif