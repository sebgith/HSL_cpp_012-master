#include <pinConfig.h>

/*
                                         ----------------
                                      ++|3.3V         GND|**
                                      --|EN           G23|-- MOSI (SD-Port)
                                      --|SP           G22|-- SCL (ADC)
                                      --|SN           TXD|--
      (Input only no pullup or down)  --|G34          RXD|--
      (Input only no pullup or down)  --|G35          G21|-- SDA (ADC)
                             rpmPin_1 --|G32          GND|**
                     checkSdInsertPin --|G33          G19|-- MISO (SD-Port)
                             rpmPin_2 --|G25          G18|-- SCK/CLK (SD-Port)
                             rpmPin_3 --|G26           G5|-- sdPin
                            rxdGpsPin --|G27          G17|-- icOutputpin_4
                            txdGpsPin --|G14          G16|-- icOutputpin_3
                    Funktionsschalter --|G12           G4|-- redLedPin
                                      **|GND           G0|-- icOutputpin_1
                        icOutputpin_2 --|G13           G2|-- blueLedPin
                                   XXX--|SD2          G15|-- greenLedPin
                                   XXX--|SD3          SD1|--XXX
                                      **|GND          SD0|--XXX
                                      ++|5V           CLK|--XXX
                                         ----------------
                                              |USB|
*/

//------------ variables RPM -----------------------
const int rpmPin_1 = 32;  // Pin für Drehzahlsensor
const int rpmPin_2 = 25; // Pin für Drehzahlsensor
const int rpmPin_3 = 26;  // Pin für Drehzahlsensor

//------------ led -----------------------
const int greenLedPin = 15; // Pin für led
const int blueLedPin = 2;   // Pin für led
const int redLedPin = 4;    // Pin für led

//------------ sd card -----------------------
const int sdPin = 5;             // Pin für SD-card Input (CS)
const int checkSdInsertPin = 33; // Pin for reading if SD is insert

//------------ gps -----------------------
const int rxdGpsPin = 27;  // Pin für Kommunikation mit GPS Modul
const int txdGpsPin = 14;  // Pin für Kommunikation mit GPS Modul

//----------------- ic -----------------
const int icOutputpin_1 = 0; 
const int icOutputpin_2 = 13;
const int icOutputpin_3 = 16;
const int icOutputpin_4 = 17;