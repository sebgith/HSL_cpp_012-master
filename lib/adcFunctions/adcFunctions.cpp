#include <adcFunctions.h>
#include <Adafruit_ADS1X15.h>
#include <parameterConfig.h>
#include <globalObjAndVar.h>
#include <adcClass.h>
#include <sdCard.h>

//*******************************************************
// ----------------- general functions ---------------

unsigned long  adcInputCalc::_previousMillisAdcRead = 0;
unsigned long adcInputCalc::_durationSincePreviousAdcRead;
float adcInputCalc::_selectedGain;

void setupAdcConfig()
{
    ads.begin(); // start ADC
    // ads.setRate(ADS1115_RATE_20); //Abtastrate 8 SPS
    // ads.setMode(ADS1115_MODE_CONTINUOUS); //Kontinuierliche Messung   CONTINUOUS BEI LIBRARY ADAFRUIT NICHT FÜR 1115 verfügbar
    // ads.mode = Mode.CONTINUOUS;
    /*#define RATE_ADS1115_8SPS (0x0000)   ///< 8 samples per second
    #define RATE_ADS1115_16SPS (0x0020)  ///< 16 samples per second
    #define RATE_ADS1115_32SPS (0x0040)  ///< 32 samples per second
    #define RATE_ADS1115_64SPS (0x0060)  ///< 64 samples per second
    #define RATE_ADS1115_128SPS (0x0080) ///< 128 samples per second (default)
    #define RATE_ADS1115_250SPS (0x00A0) ///< 250 samples per second
    #define RATE_ADS1115_475SPS (0x00C0) ///< 475 samples per second
    #define RATE_ADS1115_860SPS (0x00E0) ///< 860 samples per second*/
    ads.setDataRate(RATE_ADS1115_860SPS);
    // calc gain
    float maxInputMilliVoltAll = max(max(adcObj_0.getMaxExpectedMilliVolt(),
                                         adcObj_1.getMaxExpectedMilliVolt()),
                                     max(adcObj_2.getMaxExpectedMilliVolt(),
                                         adcObj_3.getMaxExpectedMilliVolt()));

    if (maxInputMilliVoltAll < 1000.0)
    {
        Serial.println("ADC Gain 1V");
        ads.setGain(GAIN_FOUR);
        adcInputCalc::_selectedGain = 1024.0;
    }
    else if (maxInputMilliVoltAll < 2000.0)
    {
        Serial.println("ADC Gain 2V");
        ads.setGain(GAIN_TWO);
        adcInputCalc::_selectedGain = 2048.0;
    }
    else if (maxInputMilliVoltAll < 4000.0)
    {
        Serial.println("ADC Gain 4V");
        ads.setGain(GAIN_ONE);
        adcInputCalc::_selectedGain = 4096.0;
    }
    else
    { // up to 6.144 Volt input allowed
        Serial.println("ADC Gain 6V");
        ads.setGain(GAIN_TWOTHIRDS);
        adcInputCalc::_selectedGain = 6144.0;
    }
}

void adcReadAndCalc()
{
    unsigned long currentMillis = millis();
    adcInputCalc::_durationSincePreviousAdcRead = currentMillis - adcInputCalc::_previousMillisAdcRead;
    adcInputCalc::_previousMillisAdcRead = currentMillis;

    int digitalAdcReadValue_0 = ads.readADC_SingleEnded(0); // read external ADC values
    int digitalAdcReadValue_1 = ads.readADC_SingleEnded(1); // read external ADC values
    int digitalAdcReadValue_2 = ads.readADC_SingleEnded(2); // read external ADC values
    int digitalAdcReadValue_3 = ads.readADC_SingleEnded(3); // read external ADC values

    adcObj_0.calcFilteredPhysAdcValue(digitalAdcReadValue_0); // calc filtered physical values
    adcObj_1.calcFilteredPhysAdcValue(digitalAdcReadValue_1); // calc filtered physical values
    adcObj_2.calcFilteredPhysAdcValue(digitalAdcReadValue_2); // calc filtered physical values
    adcObj_3.calcFilteredPhysAdcValue(digitalAdcReadValue_3); // calc filtered physical values

    if (sdCardReady())
    {
        String dataString = "";
        dataString += String(digitalAdcReadValue_0);
        dataString += ",";
        dataString += String(digitalAdcReadValue_1);
        dataString += ",";
        dataString += String(digitalAdcReadValue_2);
        dataString += ",";
        dataString += String(digitalAdcReadValue_3);
        dataString += ",";
        dataString += String(adcInputCalc::_durationSincePreviousAdcRead);
        writeDataToSdCard(dataString);
        blueLed.blinkLed(500); // blink LED while data logging is active
        Serial.println("logging data");
    }
}