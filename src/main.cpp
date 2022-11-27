
#include <Arduino.h>
#include <led.h>
#include <rpm.h>
#include <sdCard.h>
#include <pinConfig.h>
#include <parameterConfig.h>
#include <Adafruit_ADS1X15.h>
#include <WifiUdp.h>
#include <wifiFunctions.h>
#include <WiFi.h>
#include <mqtt.h>
// #include <SoftwareSerial.h> - if compiles -> can be removed
#include <gpsFunctions.h>
#include <adcFunctions.h>
#include <icControl.h>
#include <EEPROM.h>
#include <wifi_webInterface.h>
#include <globalObjAndVar.h>

unsigned long currentMillis;

unsigned long previousMillisLoop = 0;
unsigned long durationLoop;

unsigned long previousMillisRpm = 0;
int RpmCalcInterval = 1000;

unsigned long previousMillisPublishMqtt = 0;
int publishMqttInterval = 2000;

void setup()
{
  Serial.begin(9600);
  //-------------- setup rpm ----------------
  setupRpm();
  //-------------- sd card checker  ----------------
  pinMode(checkSdInsertPin, INPUT_PULLUP); // set pin to check connection
  
  //-------------- set IC output ----------------
  pinMode(icOutputpin_1, OUTPUT);
  pinMode(icOutputpin_2, OUTPUT);
  pinMode(icOutputpin_3, OUTPUT);
  pinMode(icOutputpin_4, OUTPUT);
  digitalWrite(icOutputpin_1,  LOW);
  digitalWrite(icOutputpin_2,  LOW);
  digitalWrite(icOutputpin_3,  LOW);
  digitalWrite(icOutputpin_4,  LOW);


  setupWebInterface(); // Browser UI Startet normalerweise auch in serialmonitor mit 115000

  wifi_init(); // start wifi

  reconnectMqttTb(); // start thingsboard connection

  gpsSerial.begin(9600); // seriellen Teilnehmer erstellen

  setupAdcConfig();
  
  //UpdateVariableswithUserInput(); // Müssen schauen wo wir diese funktion ausführen
}

void loop()
{
  iotWebConf.doLoop(); // UI
  currentMillis = millis();
  durationLoop = currentMillis - previousMillisLoop;
  previousMillisLoop = currentMillis;
  Serial.print("Time since last measurement: ");
  Serial.println(durationLoop);

  currentMillis = millis();
  if (currentMillis - previousMillisRpm >= RpmCalcInterval) // update rpm every second (RpmCalcInterval)
  {
    firstRpm.calcRpm();
    secondRpm.calcRpm();
    thirdRpm.calcRpm();
    calcRpmRatio(&firstRpm, &secondRpm);
    previousMillisRpm = currentMillis;
  }

  //-----------------time since last measurement------------
  adcReadAndCalc();

 // checkSDavailable();

  getGpsData(); // jede loop????? eher alle 5 Sekunden??

  icControl();
  // --------------------- mqtt publish -----------------------------
  currentMillis = millis();
  if (currentMillis - previousMillisPublishMqtt >= publishMqttInterval)
  {
    previousMillisPublishMqtt = currentMillis;
    if (WiFi.status() != WL_CONNECTED) // check wifi connection
    {
      wifi_init();
    }
    publishMqtt(durationLoop);
  }

  //--------------------MQTT Status LED -------------------------------
  if (cntTbMqttRetry == 0) // no retries -> connected
  {
    digitalWrite(greenLed.getLedPin(), HIGH); // ON: thingsboard connected
  }
  else
  {
    greenLed.blinkLed(500); // blink: not connected to thingsboard
  }

  clientTb.loop();
}