#ifndef CONTROL_H
#define CONTROL_H

#include <Arduino.h>

class Control
{
public:
    Control(int _relayPin);
    void mainsOn();
    void mainsOff();

private:
    int relayPin;
};
#endif