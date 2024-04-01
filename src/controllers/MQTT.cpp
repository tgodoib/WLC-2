#include "controllers/MQTT.h"

WiFiClientSecure MQTT::wifiClient;
PubSubClient MQTT::mqttClient(wifiClient);

time_t MQTT::now = 0;
time_t MQTT::lastReconnectTry = 0;

void MQTT::init() {
    MQTT::configNTP();

    wifiClient.setCACert(cacert);
    wifiClient.setCertificate(client_cert);
    wifiClient.setPrivateKey(privkey);

    mqttClient.setServer(MQTT_HOST, 8883);
    mqttClient.setCallback(MQTT::receive);

    LOG::debug("MQTT", "Configured MQTT, waiting for connection.");
    MQTT::connect();
}

void MQTT::loop() {
//    LOG::debug("MQTT", "looping 1");
    now = time(nullptr);
//    LOG::debug("MQTT", "looping 2");
    if (!mqttClient.connected() /*&& now - lastReconnectTry >= 5*/) MQTT::connect();

//    LOG::debug("MQTT", "looping 3");
    mqttClient.loop();
//    LOG::debug("MQTT", "looping 4");
}

void MQTT::configNTP() {
    LOG::info("NTP", "Configuring time.");
    configTime(-3 * 3600, 0 * 3600, "a.st1.ntp.br", "b.st1.ntp.br");

    while (now < 1671764400) {
        delay(500);
        Serial.print(".");
        now = time(nullptr);
    }
    LOG::line();

    struct tm timeInfo{};
    gmtime_r(&now, &timeInfo);

   LOG::info_nl("NTP", "Current time: ");
   LOG::info("", asctime(&timeInfo));
}

String MQTT::error_code(int MQTTErr) {
    if      (MQTTErr == MQTT_CONNECTION_TIMEOUT) return "Connection tiemout";
    else if (MQTTErr == MQTT_CONNECTION_LOST) return "Connection lost";
    else if (MQTTErr == MQTT_CONNECT_FAILED) return "Connect failed";
    else if (MQTTErr == MQTT_DISCONNECTED) return "Disconnected";
    else if (MQTTErr == MQTT_CONNECTED) return "Connected";
    else if (MQTTErr == MQTT_CONNECT_BAD_PROTOCOL) return "Connect bad protocol";
    else if (MQTTErr == MQTT_CONNECT_BAD_CLIENT_ID) return "Connect bad Client-ID";
    else if (MQTTErr == MQTT_CONNECT_UNAVAILABLE) return "Connect unavailable";
    else if (MQTTErr == MQTT_CONNECT_BAD_CREDENTIALS) return "Connect bad credentials";
    else if (MQTTErr == MQTT_CONNECT_UNAUTHORIZED) return "Connect unauthorized";
    return "Unknown Error";
}

void MQTT::connect() {
    LOG::info("MQTT", "Trying to connect...");
    if (!mqttClient.connect("WLC")) {
        LOG::error("MQTT", "Failed to connect. Trying again in 5s.");
        lastReconnectTry = now;
        return;
    }

    LOG::info("MQTT", "Connected.");
    if (!mqttClient.subscribe("HSV")) {
        LOG::error("MQTT", "Error subscribing to HSV: " + MQTT::error_code(mqttClient.state()));
    }
    if (!mqttClient.subscribe("Preset")) {
        LOG::error("MQTT", "Error subscribing to Preset: " + MQTT::error_code(mqttClient.state()));
    }
    if (!mqttClient.subscribe("Value")) {
        LOG::error("MQTT", "Error subscribing to Value: " + MQTT::error_code(mqttClient.state()));
    }
    LOG::debug("MQTT", "Subscribed to channels.");
}

void MQTT::publish(char *topic, char *payload) {
    mqttClient.publish(topic, payload);
}

void MQTT::receive(char *topic, byte *payload, unsigned int length) {
    if(String(topic).equals("HSV")) {
        StaticJsonDocument<96> doc;
        DeserializationError error = deserializeJson(doc, payload, length);

        if (error) {
            LOG::error("MQTT", String("deserializeJson() failed -> ") + String(error.f_str()));
            return;
        }

        bool fade = doc["fade"];
        bool keep_value = doc["keep_value"];

        JsonArray color = doc["color"];
        int h = color[0];
        int s = color[1];
        int v = 255;

        LOG::debug("MQTT][HSV", String(h) + ", " + String(s) + ", "+String(v));

        LED::setPreset(PresetType::SOLID);
        LED::config(new CHSV(h, s, v));
        LED::start(fade);
    }

    else if(String(topic).equals("Value")) {
        StaticJsonDocument<16> doc;
        DeserializationError error = deserializeJson(doc, payload, length);

        if (error) {
            LOG::error("MQTT", String("deserializeJson() failed -> ") + String(error.f_str()));
            return;
        }

        int value = doc["value"];

        LOG::debug("MQTT][Value", String(value));

        LED::setBrightness(value, true);
    }
}
