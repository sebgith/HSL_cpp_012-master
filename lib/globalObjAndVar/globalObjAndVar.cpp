#include <globalObjAndVar.h>
#include <Adafruit_ADS1X15.h>
#include <adcClass.h>
#include <rpm.h>
#include <led.h>
#include <parameterConfig.h>
#include <pinConfig.h>

Adafruit_ADS1115 ads; // create ADC Object

adcInputCalc adcObj_0(physicalMinAdc_0,
                      physicalMaxAdc_0,
                      minCurrentAdc_0,
                      maxCurrentAdc_0,
                      filterAdc_0,
                      resistorAdc_0);

adcInputCalc adcObj_1(physicalMinAdc_1,
                      physicalMaxAdc_1,
                      minCurrentAdc_1,
                      maxCurrentAdc_1,
                      filterAdc_1,
                      resistorAdc_1);

adcInputCalc adcObj_2(physicalMinAdc_2,
                      physicalMaxAdc_2,
                      minCurrentAdc_2,
                      maxCurrentAdc_2,
                      filterAdc_2,
                      resistorAdc_2);

adcInputCalc adcObj_3(physicalMinAdc_3,
                      physicalMaxAdc_3,
                      minCurrentAdc_3,
                      maxCurrentAdc_3,
                      filterAdc_3,
                      resistorAdc_3);

rpm firstRpm(rpmPin_1, filterRpm_1);
rpm secondRpm(rpmPin_2, filterRpm_2);
rpm thirdRpm(rpmPin_3, filterRpm_3);

led greenLed(greenLedPin); // Objekt für led erstellen mit Pin Zuweisung
led blueLed(blueLedPin);   // Objekt für led erstellen mit Pin Zuweisung
led redLed(redLedPin);     // Objekt für led erstellen mit Pin Zuweisung


float ratioRpmUpload;
