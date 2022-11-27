#include <icControl.h>
#include <Arduino.h>
#include <pinConfig.h>
#include <adcFunctions.h>
#include <globalObjAndVar.h>

unsigned long previousMillisIc = 0;
const long intervalIc = 3000;  // Intervall für publish

void icControl(){
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillisIc >= intervalIc) {
    previousMillisIc = currentMillis;
    
    if(ratioRpmUpload<195){               //Drehzahlverhältnis kleiner 195
      digitalWrite(icOutputpin_2, HIGH);
    }
    if(adcObj_0.getFilterdPhysAdcValue() > 10) {      //Differenzdruck größer 10 mbar
      digitalWrite(icOutputpin_3, HIGH);
    }
    if(adcObj_3.getFilterdPhysAdcValue() > 70) {      //Temperatur größer 70 Grad
      digitalWrite(icOutputpin_4, HIGH);
    }
    if(0) {                               //noch nicht definiert
      digitalWrite(icOutputpin_1, HIGH);
    }
  }
}
