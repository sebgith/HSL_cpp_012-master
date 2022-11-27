/*
    class for leds
*/

#ifndef led_h
#define led_h

class led
{
public:
    led(const int ledHardwarePin); // hardware pin as a input
    int getLedPin();
    void blinkLed(int blinkRate);

private:
    const int _ledHardwarePin;
    unsigned long _previousMillisLed;
};

#endif // led_h
