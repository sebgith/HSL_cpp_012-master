#include <led.h>
#include <WiFi.h>
#include <wifiFunctions.h>
#include <globalObjAndVar.h>

//------------ wifi -----------------------
// UR 215
// const char* ssid = "RUT240_864B";
// const char* password = "q6R9AnSg";
// UR 245
// const char* ssid = "RUT240_B5D8";
// const char* password = "r3AWi1s7";
// UR 200
// const char* ssid = "RUT240_A2A1";
// const char* password = "i4FGp2n8";
// UR 180
// const char* ssid = "RUT240_380C";
// const char* password = "Ct42BsGj";

// Inbetriebnahme WiFi für OTA updates
/*
const char* ssid_ibn = "esp_ibn";
const char* password_ibn = "esp_ibn1234";
*/

// Wifi Config Basti daheim
// const char* ssid = "Vivalafritz";
// const char* password = "wirwollenwulle007";

// Wifi Config stu
const char *ssid_ibn = "pinkfluffyunicorn_2.4GHz";
const char *password_ibn = "Gl1tzerGl1tzer!";

// Wifi Config flo daheim
const char *ssid = "o2-WLAN77";
const char *password = "TPU9DV86933838Y4";

// mi phone
// const char* ssid_ibn = "Mi Phone";
// const char* password_ibn = "612ef09692e2";


WiFiUDP ntpUDP;

void wifi_init()
{
    int ledBlinkRate = 2000;
    int wifi_retry = 0;
    unsigned long previousMillisWifi = millis();
    int wifiMillisBeforeRetry = 10000;
    while (WiFi.status() != WL_CONNECTED && wifi_retry < 6)
    {
        unsigned long currentMillis = millis();
        if (currentMillis - previousMillisWifi >= wifiMillisBeforeRetry)
        {
            previousMillisWifi = currentMillis;
            Serial.println("WiFi not connected. Try to reconnect");
            WiFi.disconnect();
            WiFi.mode(WIFI_OFF);
            WiFi.mode(WIFI_STA);
            if (wifi_retry < 3)
            {
                Serial.print("Connecting to ");
                Serial.println(ssid_ibn);
                WiFi.begin(ssid_ibn, password_ibn);
            }
            else
            {
                Serial.print("Connecting to ");
                Serial.println(ssid);
                WiFi.begin(ssid, password);
                ledBlinkRate = 500;
            }
            wifi_retry++;
        }
        redLed.blinkLed(ledBlinkRate);
    }
    if (WiFi.status() != WL_CONNECTED)
    { // reboot if no wifi connection
        digitalWrite(greenLed.getLedPin(), HIGH);
        digitalWrite(blueLed.getLedPin(), HIGH);
        digitalWrite(redLed.getLedPin(), HIGH);
        Serial.println("\nReboot");
        delay(2000);
        digitalWrite(greenLed.getLedPin(), LOW);
        delay(1000);
        digitalWrite(blueLed.getLedPin(), LOW);
        delay(1000);
        digitalWrite(redLed.getLedPin(), LOW);
        ESP.restart();
        delay(500);
    }
    digitalWrite(redLed.getLedPin(), LOW); // wifi connected
    Serial.println("");
    Serial.print("Congratulations!! WiFi connected on IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println("");
    Serial.println("Now, follow up on the steps for the MQTT configuration. ");
}
