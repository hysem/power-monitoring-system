#include "display.h"

Display::Display(int rs, int en, int d4, int d5, int d6, int d7, int cols, int rows)
{
    lcd = new LiquidCrystal(rs, en, d4, d5, d6, d7);
    lcd->begin(cols, rows);
    lcd->noBlink();
}

void Display::showReadings(float voltage, float current, float pf)
{
    content = "";

    content.concat("V:");
    content.concat(String(voltage, 2));

    content.concat(" A:");
    content.concat(String(current, 2));

    lcd->clear();
    lcd->print(content);

    lcd->setCursor(0, 1);
    if (voltage < 10 && current < .1)
    {
        content = "NO SUPPLY";
    }
    else if (voltage > 200 && current < .1)
    {
        content = "NO LOAD";
    }
    else
    {
        content = "PF: ";
        content.concat(String(pf, 2));
    }
    lcd->setCursor(0, 1);
    lcd->print(content);
}

void Display::printOverloadError(float current)
{
    lcd->clear();
    lcd->print("OVERLOAD > 4 A");
}

void Display::printShortCircuitError()
{
    lcd->clear();
    lcd->print("SHORT CIRCUIT");
}