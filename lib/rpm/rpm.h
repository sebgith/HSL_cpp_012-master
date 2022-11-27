#ifndef rpm_h
#define rpm_h

#include <Arduino.h>

class rpm
{
public:
    rpm(const int rpmPin, int filterRpm);
    void updateRpmPulses();
    int getRpmPin();
    int getRpmUpload();
    void getPulses();
    void calcRpm();

private:
    static const int _millisecPerMin = 60000;
    const int _rpmPin;
    const int _filterRpm;
    unsigned long _timeStampCurrentPulseRpm;
    unsigned long _timeStampCurrentPulseRpmSaved;
    unsigned long _timeStampLastPulseRpm = 0;
    volatile int _rpmCnt = 0; // Flankenzähler für Sensor 1
    int _rpmCntSaved;
    int _rpmNew;
    int _rpmStorage[3] = {0, 0, 0};
    int _rpmUpload;
};

// additional functions for rpm calculations
void calcRpmRatio(rpm *rpmOne, rpm *rpmTwo);

// functions to call at interrupt
void IRAM_ATTR firstRpmPulseCounter();
void IRAM_ATTR secondRpmPulseCounter();
void IRAM_ATTR thirdRpmPulseCounter();

void setupRpm();

#endif // rpm_h