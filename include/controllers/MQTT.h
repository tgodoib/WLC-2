#ifndef WCL_2_MQTT_H
#define WCL_2_MQTT_H

#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <time.h>
#include "Secrets.h"
#include "infrastructure/LOG.h"
#include "controllers/LED.h"

class MQTT {
private:
    static WiFiClientSecure wifiClient;
    static PubSubClient mqttClient;

    static time_t lastReconnectTry;

    static void configNTP();
    static String error_code(int MQTTErr);

    static void connect();
    static void receive(char *topic, byte *payload, unsigned int length);

public:
    static time_t now;

    static void init();
    static void loop();

    static void publish(char *topic, char *payload);
};


#endif //WCL_2_MQTT_H
