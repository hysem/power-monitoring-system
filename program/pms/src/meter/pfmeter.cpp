#include "pfmeter.h"

PFMeter::PFMeter(int _voltageInputPin, int _currentInputPin, int _samples, int _interval)
{
    voltageInputPin = _voltageInputPin;
    currentInputPin = _currentInputPin;
    samples = _samples;
    interval = _interval;

    expectedFrequency = 50;
    voltageAnalogOffset = 0;
    currentAnalogOffset = 0;
    vAnalogValue = 0;
    iAnalogValue = 0;
    previousValueV = 0;
    previousValueI = 0;
    previousphaseAngleSample = 0;
    phaseAngleSample = 0;
    phaseAngleAccumulate = 0;
    periodSample = 0;
    periodSampleAccumulate = 0;
    phaseDifference = 0;
    phaseAngle = 0;
    frequency = 0;
    voltagePhaseAngle = 0;
    currentPhaseAngle = 0;
    averagePeriod = 0;
    sampleCount = 0;
    a = 3;

    currentOffsetRead = 0;
    currentOffsetLastSample = 0;
    currentOffsetSampleCount = 0;
    voltageOffsetRead = 0;
    voltageOffsetLastSample = 0;
    voltageOffsetSampleCount = 0;
}

float PFMeter::powerFactor()
{
    for (i == 0; i < samples; i++)
    {
        currentOffsetRead = 1;
        voltageOffsetRead = 1;

        // 1 - Phase Angle, Frequency and Power Factor measurement
        vAnalogValue = analogRead(voltageInputPin) - 512 + voltageAnalogOffset;
        iAnalogValue = analogRead(currentInputPin) - 512 + currentAnalogOffset;

        if ((vAnalogValue > 0) && a == 3)
        {
            a = 0;
        }

        if ((vAnalogValue <= 0) && a == 0)
        {
            startMicrosPA = micros();
            a = 1;
        }

        if ((vAnalogValue > 0) && a == 1)
        {
            a = 2;
            previousValueV = 0;
            previousValueI = 0;
        }

        if ((vAnalogValue > previousValueV) && a == 2)
        {
            previousValueV = vAnalogValue;
            vCurrentMicrosPA = micros();
        }

        if ((iAnalogValue > previousValueI) && a == 2)
        {
            previousValueI = iAnalogValue;
            iCurrentMicrosPA = micros();
        }

        if ((vAnalogValue <= 0) && a == 2)
        {
            periodMicrosPA = micros();
            periodSample = periodMicrosPA - startMicrosPA;
            periodSampleAccumulate = periodSampleAccumulate + periodSample;
            voltagePhaseAngle = vCurrentMicrosPA - startMicrosPA;
            currentPhaseAngle = iCurrentMicrosPA - startMicrosPA;
            phaseAngleSample = currentPhaseAngle - voltagePhaseAngle;
            if (phaseAngleSample >= 100)
            {
                previousphaseAngleSample = phaseAngleSample;
            }
            if (phaseAngleSample < 100)
            {
                phaseAngleSample = previousphaseAngleSample;
            }
            phaseAngleAccumulate = phaseAngleAccumulate + phaseAngleSample;
            sampleCount = sampleCount + 1;
            startMicrosPA = periodMicrosPA;
            a = 1;
            previousValueV = 0;
            previousValueI = 0;
        }

        // 1.1 - Phase Angle Offset

        if (voltageOffsetRead == 1)
        {
            voltageAnalogOffset = 0;
            if (millis() >= voltageOffsetLastSample + 1)
            {
                voltageOffsetSampleCount = voltageOffsetSampleCount + 1;
                voltageOffsetLastSample = millis();
            }
            if (voltageOffsetSampleCount == 1500)
            {
                vAnalogValue = analogRead(voltageInputPin) - 512 + voltageAnalogOffset;
                voltageAnalogOffset = -1 * (vAnalogValue);
                voltageOffsetRead = 0;
                voltageOffsetSampleCount = 0;
            }
        }

        if (currentOffsetRead == 1)
        {
            currentAnalogOffset = 0;
            if (millis() >= currentOffsetLastSample + 1)
            {
                currentOffsetSampleCount = currentOffsetSampleCount + 1;
                currentOffsetLastSample = millis();
            }
            if (currentOffsetSampleCount == 1500)
            {
                iAnalogValue = analogRead(currentInputPin) - 512 + currentAnalogOffset;
                currentAnalogOffset = -1 * (iAnalogValue);
                currentOffsetRead = 0;
                currentOffsetSampleCount = 0;
            }
        }
    }

    averagePeriod = periodSampleAccumulate / sampleCount;
    frequency = 1000000 / averagePeriod;
    phaseDifference = phaseAngleAccumulate / sampleCount;
    phaseAngle = ((phaseDifference * 360) / averagePeriod);
    pf = cos(phaseAngle * 0.017453292);
    Serial.print("Phase Angle :");
    Serial.print(phaseAngle, 2);
    Serial.print("° ");
    Serial.print("Frequency :");
    Serial.print(frequency, 2);
    Serial.print("Hz ");
    Serial.print("Power Factor :");
    Serial.println(pf, 2);
    sampleCount = 0;
    periodSampleAccumulate = 0;
    phaseAngleAccumulate = 0;
    return pf;
}