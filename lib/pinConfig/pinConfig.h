/*
    Library for global variables used in different source files
*/
#ifndef pinConfig_h
#define pinConfig_h

//------------ variables drehzahl calc -----------------------
extern const int rpmPin_1;                      // Pin Eingang für Sensor 1
extern const int rpmPin_2;                      // Pin Eingang für Sensor 2
extern const int rpmPin_3;                    // Pin Eingang für Sensor 2

//------------ led -----------------------
extern const int greenLedPin;                      // Pin für led
extern const int blueLedPin;                       // Pin für led
extern const int redLedPin;                        // Pin für led

//------------ SD card inputs -------------
extern const int sdPin;
extern const int checkSdInsertPin;

//------------ gps -----------------------
extern const int rxdGpsPin;  // Pin für Kommunikation mit GPS Modul
extern const int txdGpsPin;  // Pin für Kommunikation mit GPS Modul

//----------------- ic -----------------
extern const int icOutputpin_1;
extern const int icOutputpin_2;
extern const int icOutputpin_3;
extern const int icOutputpin_4;

#endif //pinConfig_h