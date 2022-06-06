#ifndef GSM_H
#define GSM_H

#include <Arduino.h>
#include <SoftwareSerial.h>

class GSM
{
public:
    GSM(int rxPin, int txPin);
    void sendSMS(String mobileNumber, String content);

private:
    SoftwareSerial *gsmSerial;
    String updateSerial();
};

#endif