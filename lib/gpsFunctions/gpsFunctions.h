#ifndef gpsFunctions_h
#define gpsFunctions_h

#include <SoftwareSerial.h>

void getGpsData();

extern SoftwareSerial gpsSerial;

extern float latitudeupload;
extern float longitudeupload;
extern float gpsspeedupload;
extern unsigned short gpssats;

#endif //gpsFunctions_h