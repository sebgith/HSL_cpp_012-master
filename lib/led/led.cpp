#include <led.h>
#include <Arduino.h>
#include <pinConfig.h>


led::led(const int ledHardwarePin)
    : _ledHardwarePin(ledHardwarePin), _previousMillisLed(0)
{
    pinMode(ledHardwarePin, OUTPUT); // set pin mode for LED
}

int led::getLedPin()
{
    return _ledHardwarePin;
}
void led::blinkLed(int blinkRate)
{
    unsigned long currentMillis = millis();
    if (currentMillis - _previousMillisLed >= blinkRate)
    {
        _previousMillisLed = currentMillis;
        digitalWrite(_ledHardwarePin, !digitalRead(_ledHardwarePin));
    }
}