#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <LiquidCrystal.h>

class Display
{
public:
    Display(int rs, int en, int d4, int d5, int d6, int d7, int cols, int rows);
    void showReadings(float voltage, float current, float pf);
    void printOverloadError(float current);
    void printShortCircuitError();

private:
    LiquidCrystal *lcd;
    String content;
};

#endif