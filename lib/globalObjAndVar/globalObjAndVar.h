#ifndef globals_h
#define globals_h
#include <adcClass.h> // ausgeschnitten von globalObjAndVar.ccp
#include <adcFunctions.h>
#include <rpm.h>
#include <led.h>
#include <Adafruit_ADS1X15.h>

extern Adafruit_ADS1115 ads;
extern adcInputCalc adcObj_0;
extern adcInputCalc adcObj_1;
extern adcInputCalc adcObj_2;
extern adcInputCalc adcObj_3;

//------------ objects drehzahl calc -----------------------
extern rpm firstRpm;
extern rpm secondRpm;
extern rpm thirdRpm;

//------------ objects led -----------------------
extern led greenLed; // Objekt für led erstellen mit Pin Zuweisung
extern led blueLed;   // Objekt für led erstellen mit Pin Zuweisung
extern led redLed;     // Objekt für led erstellen mit Pin Zuweisung


extern float ratioRpmUpload;


#endif // globals_h