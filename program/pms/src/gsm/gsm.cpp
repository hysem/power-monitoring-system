#include "gsm.h"

GSM::GSM(int rxPin, int txPin)
{
    pinMode(rxPin, INPUT);
    pinMode(txPin, OUTPUT);
    gsmSerial = new SoftwareSerial(rxPin, txPin);
    gsmSerial->begin(9600);
}

void GSM::sendSMS(String mobileNumber, String content)
{
    // Serial.println ("Sending Message");
    gsmSerial->println("AT+CMGF=1"); // Sets the GSM Module in Text Mode
    delay(200);
    // Serial.println ("Set SMS Number");
    String cmd = "AT+CMGS=\"";
    cmd.concat(mobileNumber);
    cmd.concat("\"\r");
    gsmSerial->println(cmd); // Mobile phone number to send message
    delay(200);
    gsmSerial->println(content);
    delay(100);
    gsmSerial->println((char)26); // ASCII code of CTRL+Z
    delay(200);
    String buffer = updateSerial();
    Serial.println(buffer);
}

String GSM::updateSerial()
{
    int timeout = 0;
    while (!gsmSerial->available() && timeout < 12000)
    {
        delay(13);
        timeout++;
    }
    if (gsmSerial->available())
    {
        return gsmSerial->readString();
    }
}