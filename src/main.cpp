#include <Arduino.h>
#include "infrastructure/WIFI.h"
#include "infrastructure/LOG.h"
#include "controllers/LED.h"
#include <FastLED.h>
#include "infrastructure/RENDER.h"
#include "controllers/MQTT.h"
//#include "controllers/HomeKit.h"

void setup() {
    LOG::init();
    WIFI::connect();

    RENDER::init();
    LED::init();

    MQTT::init();

    DATA::init();

//    HomeKit::init();

    delay(1000);
    FastLED.clear(true);

    RENDER::setBrightness(DATA::getBrightness());
    LED::setPreset(DATA::getPreset());
    char data[5];
    DATA::getPresetData(5, data);
    LED::getPreset()->restoreData(data);
    LED::start(false);
}

void loop() {
    LED::loop();
    MQTT::loop();
//    HomeKit::loop();
}