//
// Created by Tiago Bannwart on 01/04/24.
//

#include "controllers/HomeKit.h"
#include "infrastructure/RENDER.h"

SpanCharacteristic *FITA_LED::power;
SpanCharacteristic *FITA_LED::brightness;
SpanCharacteristic *FITA_LED::H;
SpanCharacteristic *FITA_LED::S;
SpanCharacteristic *FITA_LED::V;

FITA_LED::FITA_LED() : Service::LightBulb() {
    power = new Characteristic::On();
    brightness = new Characteristic::Brightness();

    H = new Characteristic::Hue();
    S = new Characteristic::Saturation();
    V = new Characteristic::Brightness();
}

boolean FITA_LED::update() {
    boolean p;
    uint8_t b;
    uint8_t v, h, s;

    h = H->getVal<uint8_t>();
    s = S->getVal<uint8_t>();
    v = V->getVal<uint8_t>();
    b = brightness->getVal<uint8_t>();
    p = power->getVal();

    if (brightness->updated()) {
        LED::setBrightness(b);
    } else if (power->updated()) {
        LED::setBrightness(p * 100);
    }

    if (H->updated() || S->updated() || V->updated()) {
        LED::setPreset(PresetType::SOLID);
        LED::config(new CHSV(h * 255 / 360, s * 255 / 100, v * 255 / 100));
        LED::start(false);
    }

    return true;
}


void HomeKit::init() {
    homeSpan.begin(Category::Lighting, "Fita LED");

    new SpanAccessory();
    new Service::AccessoryInformation();
    new Characteristic::Identify();

    new SpanAccessory();
    new Service::AccessoryInformation();
    new Characteristic::Identify();
    new FITA_LED();
}

void HomeKit::loop() {
    homeSpan.poll();
}

void HomeKit::reportColor(CHSV *color) {
    FITA_LED::H->setVal(color->h * 360 / 255);
    FITA_LED::S->setVal(color->s * 100 / 255);
    FITA_LED::V->setVal(color->v * 100 / 255);
}

void HomeKit::reportBrightness(uint8_t brightness) {
    FITA_LED::brightness->setVal(brightness);

    if (brightness == 0) {
        FITA_LED::power->setVal(0);
    } else {
        FITA_LED::power->setVal(1);
    }
}