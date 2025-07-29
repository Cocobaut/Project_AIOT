#ifndef INC_TASKMQTT_H_
#define INC_TASKMQTT_H_

#include "globals.h"

void initMQTT();
void reconnectMQTT();
void publishData(String feed, String data);
extern String getTemperature();
extern String getHumidity();

#endif /* INC_TASKMQTT_H_ */