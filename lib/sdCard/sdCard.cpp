/*
    functions for sd card reading and writing
*/

#include <led.h>
#include <pinConfig.h>
#include <Arduino.h>
#include <NTPClient.h>
#include <SD.h>
#include <wifiFunctions.h>
#include <sdCard.h>
#include <globalObjAndVar.h>

int restartDataLog = 0;   // flag wenn SD Karte entfernt wird um Zeitstempel neu zu schreiben
bool NoSDcard;            // state if SD is insert
bool NoSDcardOld = false; // state if SD is insert previous cycle

int timeSinceSDstateChanged = 0;  // duration since SD state has changed
unsigned long lastSDstateChange;  // time when SD state has changed
int SDstateChangeAccepted = 3000; // wait 3 seconds before accept SD card change

boolean sdCardReady()
{
    NoSDcard = digitalRead(checkSdInsertPin); // 1 = no SD; 0 = SD insert
    if (NoSDcardOld != NoSDcard)
    { // gab es eine Änderung des Zustands der SD Karte, dann reset
        timeSinceSDstateChanged = 0;
        lastSDstateChange = millis();
        NoSDcardOld = NoSDcard;
        restartDataLog = 0;
        Serial.println("sd card change state");
        if (NoSDcard)
        { // no SD card avilable
            digitalWrite(blueLedPin, HIGH);
            Serial.println("no sd card");
        }
        return false; // es gab einen wechsel des Zustandes ob die SD card vorhanden ist
    }
    else if (timeSinceSDstateChanged < SDstateChangeAccepted)
    {
        timeSinceSDstateChanged = millis() - lastSDstateChange;
        Serial.println(timeSinceSDstateChanged);
        return false; // Zustand liegt noch nicht lange genug an, also weiter zählen wie lange der Zustand gleich bleibt
    }
    else if (NoSDcard) // sd card not available
    {
        return false; 
    }
    else
    {
        return true; // SD card vorhanden und kann beschrieben werden
    }
}

void writeDataToSdCard(String dataString)
{ // if SD card is available log data
    if (restartDataLog == 0)
    {
        Serial.print("Initializing SD card...");
        if (!SD.begin(sdPin))
        {
            Serial.println("Card failed, or not present");
        }
        else
        {
            Serial.println("card initialized.");
            File dataFile = SD.open("/datalog.txt", FILE_APPEND);
            dataFile.close();
            restartDataLog = 1;
        }
    }
    else if (restartDataLog == 1)
    { // Karte ist initialisiert und wird zum ersten mal beschrieben
        File dataFile = SD.open("/datalog.txt", FILE_APPEND);
        if (dataFile)
        {
            dataFile.println("...");
            dataFile.println(getTimeStamp());
            dataFile.println("...");
            dataFile.println(dataString);
            dataFile.close();
            restartDataLog = 2; // Zeitstempel geschrieben --> Zustand zwei weitere Daten können geschrieben werden
        }
        else
        {
            restartDataLog = 0; // could not open the file
        }
    }
    else if (restartDataLog == 2)
    {
        File dataFile = SD.open("/datalog.txt", FILE_APPEND);
        if (dataFile)
        {
            dataFile.println(dataString);
            dataFile.close();
        }
        else
        {
            restartDataLog = 0; // could not open the file
        }
    }
}

//******************************************************************************************
// -------------------Function to get date and time from NTPClient-------------------------
String getTimeStamp()
{

    //------------ NTP Client -----------------------
    NTPClient timeClient(ntpUDP);
    timeClient.begin();             // Initialize a NTPClient to get time
    timeClient.setTimeOffset(7200); // set offset for timezone e.g. GMT +1 = 3600

    while (!timeClient.update())
    {
        timeClient.forceUpdate();
    }
    // The formattedDate comes with the following format:
    // 2018-05-28T16:00:13Z
    // We need to extract date and time
    String formattedDate = timeClient.getFormattedDate();
    Serial.println(formattedDate);
    return formattedDate;
    /*
      // Extract date
      int splitT = formattedDate.indexOf("T");
      String dayStamp = formattedDate.substring(0, splitT);
      Serial.println(dayStamp);
      // Extract time
      String timeStamp = formattedDate.substring(splitT+1, formattedDate.length()-1);
      Serial.println(timeStamp);
    */
}