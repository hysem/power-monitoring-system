#include "src/config/config.h"
#include "src/control/control.h"
#include "src/meter/voltmeter.h"
#include "src/meter/ammeter.h"
#include "src/meter/pfmeter.h"
#include "src/display/display.h"
#include "src/gsm/gsm.h"
#include <SoftwareSerial.h>

Display display(
    LCD_RS,
    LCD_EN,
    LCD_D4,
    LCD_D5,
    LCD_D6,
    LCD_D7,
    LCD_COLS,
    LCD_ROWS);

Voltmeter voltmeter(
    VOLTMETER_INPUT_PIN,
    VOLTMETER_SAMPLES,
    VOLTMETER_INTERVAL,
    VOLTMETER_OFFSET,
    ADC_REFERENCE_VOLTAGE,
    TRANSFORMER_PRIMARY_VOLTAGE,
    VOLTMETER_RESISTOR_SMALL,
    VOLTMETER_RESISTOR_LARGE);

Ammeter ammeter(
    AMMETER_INPUT_PIN,
    AMMETER_SAMPLES,
    AMMETER_INTERVAL,
    AMMETER_OFFSET,
    ADC_REFERENCE_VOLTAGE,
    AMMETER_SENSITIVITY);

Control control(
    RELAY_PIN);

GSM gsm(
    GSM_RX_PIN,
    GSM_TX_PIN);

PFMeter pfMeter(
    VOLTMETER_INPUT_PIN,
    AMMETER_INPUT_PIN,
    PFMETER_SAMPLES,
    PFMETER_INTERVAL);

void setup()
{
  analogReference(EXTERNAL);
  control.mainsOn();
  Serial.begin(9600);
}

float voltage;
float current;
float pf;
int overCurrentFlag = 0;
int shortCircuitFlag = 0;
void loop()
{
  if (current > MAX_CURRENT_LIMIT)
  {
    control.mainsOff();
    display.printOverloadError(current);
    if (overCurrentFlag == 1)
    {
      gsm.sendSMS(SMS_NUMBER, "Over load");
      overCurrentFlag = 0;
    }
    delay(1000);
    return;
  }
  if (shortCircuitFlag == 1 || digitalRead(SHORT_CIRCUIT_BTN_PIN) == LOW)
  {
    control.mainsOff();
    display.printShortCircuitError();
    if (shortCircuitFlag == 0)
    {
      gsm.sendSMS(SMS_NUMBER, "Short Circuit");
      shortCircuitFlag = 1;
    }
    delay(1000);
    return;
  }

  delay(2500);
  overCurrentFlag = 1;
  shortCircuitFlag = 0;
  voltage = voltmeter.voltage();
  current = ammeter.current();
  pf = pfMeter.powerFactor();
  display.showReadings(voltage, current, pf);
}
