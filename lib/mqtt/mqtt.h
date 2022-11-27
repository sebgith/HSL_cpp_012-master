#ifndef mqtt_h
#define mqtt_h

#include <ThingsBoard.h>

void publishMqtt(unsigned long durationLoop);
void reconnectMqttTb();

extern int cntTbMqttRetry;

extern ThingsBoard clientTb;

#endif // mqtt_h