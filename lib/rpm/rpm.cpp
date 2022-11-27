/*
    all functions to read and evaluate the rpm sensor inputs
*/

#include <rpm.h>
#include <led.h>
#include <adcFunctions.h>
#include <Adafruit_ADS1X15.h>
#include <Arduino.h>
#include <parameterConfig.h>
#include <pinConfig.h>
#include <globalObjAndVar.h>

rpm::rpm(const int rpmPin, int filterRpm) : _rpmPin(rpmPin),
                                            _filterRpm(filterRpm)
{
    pinMode(rpmPin, INPUT); // Eingangspin auf Eingang stellen
}

void rpm::updateRpmPulses()
{
    _timeStampCurrentPulseRpm = millis();
    _rpmCnt++;
}

int rpm::getRpmPin()
{
    return _rpmPin;
}

int rpm::getRpmUpload()
{
    return _rpmUpload;
}

void rpm::getPulses()
{ // get number of pulses since last call of getPulses()
    _timeStampCurrentPulseRpmSaved = _timeStampCurrentPulseRpm;
    _rpmCntSaved = _rpmCnt;
    _rpmCnt = 0;
}

void rpm::calcRpm()
{
    this->getPulses();
    unsigned long deltaTimeRpm = _timeStampCurrentPulseRpmSaved - _timeStampLastPulseRpm; // get delta time between pulses
    _timeStampLastPulseRpm = _timeStampCurrentPulseRpmSaved;
    // get new rpm value and filter
    if (deltaTimeRpm == 0)
    {
        _rpmStorage[0] = 0;
    }
    else
    {
        float tauRpm = _filterRpm / (deltaTimeRpm);                          // calc filter value
        _rpmNew = _rpmCntSaved * _millisecPerMin / deltaTimeRpm;             // calc new RPM
        _rpmStorage[0] = (_rpmStorage[0] * tauRpm + _rpmNew) / (tauRpm + 1); // Filter the new rpm value
    }

    /// prüfen ob zweimal gradienten Wechsl stattfindet (für beide Richtungen)
    if (((_rpmStorage[0] > _rpmStorage[1]) && (_rpmStorage[1] < _rpmStorage[2])) || ((_rpmStorage[0] < _rpmStorage[1]) && (_rpmStorage[1] > _rpmStorage[2])))
    {
        int rpmOldDelta = abs(_rpmStorage[2] - _rpmStorage[1]);
        if (rpmOldDelta > 20) // prüfen ob Änderung relvant
        {
            int rpmNewDelta = abs(_rpmStorage[1] - _rpmStorage[0]);
            if (rpmNewDelta * 0.7 < rpmOldDelta && rpmNewDelta * 1.3 > rpmOldDelta) // prüfen ob erster und zweiter Sprung ungefähr gleich groß sind
            {
                _rpmStorage[1] = _rpmStorage[0]; // überschreibt [1] bevor der Wert auf [2] kopiert wird --> ausreisser Wert wird damit überschrieben
            }
        }
    }

    _rpmUpload = _rpmStorage[2]; // Wert weitergeben an upload
    // ----- Schieberegister ------
    _rpmStorage[2] = _rpmStorage[1];
    _rpmStorage[1] = _rpmStorage[0];
}

//*************************************************************************************************
// -------------------------- calc RPM ratio ----------------------------------

void calcRpmRatio(rpm *rpmOne, rpm *rpmTwo)
{
    if (rpmOne->getRpmUpload() == 0 || rpmTwo->getRpmUpload() == 0)
    {
        ratioRpmUpload = 0;
    }
    else
    {
        ratioRpmUpload = float(rpmOne->getRpmUpload()) / float(rpmTwo->getRpmUpload()) * 100;
    }
}

//-------------- rpm objects ----------------
void setupRpm()
{
    //-------------- attach interrupt for rpm ----------------
    attachInterrupt(digitalPinToInterrupt(firstRpm.getRpmPin()), firstRpmPulseCounter, FALLING);
    attachInterrupt(digitalPinToInterrupt(secondRpm.getRpmPin()), secondRpmPulseCounter, FALLING);
    attachInterrupt(digitalPinToInterrupt(thirdRpm.getRpmPin()), thirdRpmPulseCounter, FALLING);
}
//#####################################
// fucntions called on the interrupt

void IRAM_ATTR firstRpmPulseCounter()
{
    firstRpm.updateRpmPulses();
}

void IRAM_ATTR secondRpmPulseCounter()
{
    secondRpm.updateRpmPulses();
}

void IRAM_ATTR thirdRpmPulseCounter()
{
    thirdRpm.updateRpmPulses();
}