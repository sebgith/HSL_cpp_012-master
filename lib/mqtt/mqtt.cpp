#include <mqtt.h>
#include <WiFi.h>
#include <ThingsBoard.h>
#include <gpsFunctions.h>
#include <adcFunctions.h>
#include <globalObjAndVar.h>

//----------mqtt-Thingsboard--------------
#define THINGSBOARD_SERVER "iot-kehren.goip.de"
// Testgerät: "eDkzddGGZ2MMJNm45xDa"
// LB-UR-195: "SDK6BTITexEGo0egCdRK"
// LB-UR-215: "0Ei28almAdJTaqibm8n2"
#define TOKEN "eDkzddGGZ2MMJNm45xDa"

const char *topicTbAdc0 = "druck_Differenz";
const char *topicTbAdc1 = "druck_Hydraulik";
const char *topicTbAdc2 = "druck_Frischwasser";
const char *topicTbAdc3 = "Temperatur";
const char *topicTbRpm1 = "drehzahl";
const char *topicTbRpm2 = "drehzahl2";
const char *topicTbRpm3 = "drehzahl3";
const char *topicTbRatioRpm = "Rpm1zuRpm2";

const char *topicTbLatitude = "latitude";
const char *topicTbLongitude = "longitude";
const char *topicTbGpsAnzahlSatellitten = "GPSAnzahlSatellitten";
const char *topicTbGpsSpeed = "GPSGeschwindigkeit";

const char *topicTbLoopTime = "dauerLoop";

//---- WIFI name vergeben --------
WiFiClient espClientTb;
ThingsBoard clientTb(espClientTb);

const long mqttReconnection = 60000;
int connectionRetryBeforeRestart = 4;

unsigned long lastConnectionTb = 0;
int cntTbMqttRetry = 0;

void publishMqtt(unsigned long durationLoop)
{
  if (!clientTb.connected())
  {
    unsigned long currentMillis = millis();
    if (currentMillis - lastConnectionTb >= mqttReconnection)       // wenn zu lange keine Verbindung bestand--> reconnection
    {
      lastConnectionTb = currentMillis;
      reconnectMqttTb();
    }
  }
  else
  {
    Serial.println("publish Thingsboard");
    clientTb.sendTelemetryFloat(topicTbAdc3, adcObj_0.getFilterdPhysAdcValue());
    clientTb.sendTelemetryFloat(topicTbAdc2, adcObj_1.getFilterdPhysAdcValue());
    clientTb.sendTelemetryFloat(topicTbAdc1, adcObj_2.getFilterdPhysAdcValue());
    clientTb.sendTelemetryFloat(topicTbAdc0, adcObj_3.getFilterdPhysAdcValue());
    clientTb.sendTelemetryFloat(topicTbRpm1, firstRpm.getRpmUpload());
    clientTb.sendTelemetryFloat(topicTbRpm2, secondRpm.getRpmUpload());
    clientTb.sendTelemetryFloat(topicTbRpm3, thirdRpm.getRpmUpload());
    clientTb.sendTelemetryFloat(topicTbRatioRpm, ratioRpmUpload);
    if (gpssats > 5)
    {
      clientTb.sendTelemetryFloat(topicTbLatitude, latitudeupload);
      clientTb.sendTelemetryFloat(topicTbLongitude, longitudeupload);
    }
    clientTb.sendTelemetryFloat(topicTbGpsAnzahlSatellitten, gpssats);
    clientTb.sendTelemetryFloat(topicTbGpsSpeed, gpsspeedupload);
    clientTb.sendTelemetryFloat(topicTbLoopTime, durationLoop);
  }
}

// ------------------------- Thingsboard reconect----------------------------
// reconnect versuche in seriellen monitor schreiben
void reconnectMqttTb()
{
  Serial.print("Attempting to connect MQTT Tb...");
  Serial.print("Connecting to: ");
  Serial.print(THINGSBOARD_SERVER);
  Serial.print(" with token ");
  Serial.println(TOKEN);
  if (clientTb.connect(THINGSBOARD_SERVER, TOKEN))
  { // reconnection
    Serial.println("connected");
    cntTbMqttRetry = 0;
  }
  else if (cntTbMqttRetry > connectionRetryBeforeRestart)
  {
    delay(500);
    ESP.restart();
    delay(500);
  }
  else
  {
    Serial.print(" Still not connected...");     // Serial.print(client.state());
    Serial.println(" trying again in 1 minute"); // Wait 5 seconds before retrying
    cntTbMqttRetry++;
  }
}
