#include <gpsFunctions.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <pinConfig.h>

/* in diesem Tab stehen alle Anpassunge um GPS Ortung in den bestehenden code( vom 29.1221) zu itegrieren.
zwei notwendige libs sind im erstern Tab eingefügt.
HW:
RX TX müssen von GPS modul zu eingang auf dem ESP verdreht sein. rx->tx, tx->rx

Serial Baudrate auf 9600 reduziert im setup, da das NEO 6M GPS Modul dies benötigt /stabiler läuft.

2 variablen hinzugefügt in 01_variables
mqtt Grafana message erweitert

Der rest ist im loop enthalten mit entsprechendem kommentar

Doku zur tiny gps lib:
http://arduiniana.org/libraries/tinygps/

*/
float latitudeupload;
float longitudeupload;
float gpsspeedupload;
unsigned short gpssats;

SoftwareSerial gpsSerial(rxdGpsPin, txdGpsPin);
TinyGPSPlus tinyGps;

void getGpsData()
{
    while (gpsSerial.available() > 0) // geht in die schleife wenn im seriellen puffer der instanz gpsserial daten verfügbar sind >0
    {
        tinyGps.encode(gpsSerial.read()); // .read gibt die rohe NMEA codierte Information vom GPS Modul, diese wird durch die funktion .encode in das objekt tinyGps
                                          // in längen/breiten/höhe/Zeit informationen übersetzt. .encode gibt als rückgabe true/false zurück.
                                          // char c = gpsSerial.read();
        // Serial.write(c);
        // tinyGps.encode(c);
        if (tinyGps.location.isUpdated())
        {
            Serial.print("Latitude = ");
            latitudeupload = tinyGps.location.lat(), 6;
            Serial.println(latitudeupload); // ÜBER .location / .course / .speed / etc. lassen sich dann beliebige daten auslesen (DOKU in gps tab).
            Serial.print("Longitude = ");
            longitudeupload = tinyGps.location.lng(), 6;
            Serial.println(longitudeupload);
            gpsspeedupload = tinyGps.speed.kmph();
            Serial.println("gps Geschwidigkeit");
            Serial.println(gpsspeedupload);
            gpssats = tinyGps.satellites.value(); // Anzahl der Satelliten wird häufig nicht korrekt übertragen und kann dann nicht ausgegeben werden
            Serial.println("Anzahl gefundener Satelliten");
            Serial.println(gpssats);
        }
    }
}
