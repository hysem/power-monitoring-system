#include "control.h"

Control::Control(int _relayPin)
{
    relayPin = _relayPin;
    pinMode(relayPin, OUTPUT);
}

void Control::mainsOn()
{
    digitalWrite(relayPin, LOW);
}

void Control::mainsOff()
{
    digitalWrite(relayPin, HIGH);
}