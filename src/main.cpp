#include <Arduino.h>
#include "infrastructure/WIFI.h"
#include "infrastructure/LOG.h"
#include "controllers/LED.h"
#include <FastLED.h>
#include "infrastructure/RENDER.h"
#include "controllers/MQTT.h"
#include "ArduinoOTA.h"

void setup() {
    LOG::init();
    WIFI::connect();

    RENDER::init();
    LED::init();

    MQTT::init();

    DATA::init();

//    LED::setBrightness(255);

    delay(1000);
    FastLED.clear(true);

//    RENDER::fill(CHSV(HUE_PINK, 255, 255));
//    RENDER::update();

//    LED::setPreset(PresetType::SOLID);
//    LED::config(new CHSV(HUE_PINK,255,255));
//    LED::start(false);

//    LED::setBrightness(DATA::getBrightness(), false);

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
//    ArduinoOTA.handle();
}