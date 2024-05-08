//
// Created by Tiago Bannwart on 01/04/24.
//

#include "controllers/HomeKit.h"
#include "infrastructure/RENDER.h"

SpanCharacteristic *FITA_LED::power;
SpanCharacteristic *FITA_LED::H;
SpanCharacteristic *FITA_LED::S;
SpanCharacteristic *FITA_LED::V;

FITA_LED::FITA_LED() : Service::LightBulb() {
    power = new Characteristic::On();

    H = new Characteristic::Hue();
    S = new Characteristic::Saturation();
    V = new Characteristic::Brightness();
}

boolean FITA_LED::update() {
    boolean p;
    int v, h, s;

    h = H->getNewVal<int>();
    s = S->getNewVal<int>();
    v = V->getNewVal<int>();
    p = power->getNewVal<boolean>();

    CHSV newColor = CHSV(0, 0, 0);

    if (power->updated()) {
        LOG::debug("Homekit", "Power: " + String(p));
//        LED::setBrightness(p * 100);
    }

    if (V->updated()) {
        LOG::debug("Homekit", "Brightness: " + String(v));
//        LED::setBrightness(v, !(H->updated() || S->updated()));
        newColor.v = v * 255 / 100;
    }

    if (H->updated() && S->updated()) {
        LOG::debug("Homekit", "Hue: " + String(h));
        LOG::debug("Homekit", "Saturation: " + String(s));
        newColor.h = h * 255 / 360;
        newColor.s = s * 255 / 100;

//        LED::setPreset(PresetType::SOLID);
//        LED::config(&newColor);
//        LED::start();
    } else {
        if (H->updated()) {
            LOG::debug("Homekit", "Hue: " + String(h));
//            LED::setPreset(PresetType::SOLID);
//            LED::config(new CHSV(h, S->getVal() * 255 / 100, V->getVal() * 255 / 100));
//            LED::start();
        }
        if (S->updated()) {
            LOG::debug("Homekit", "Saturation: " + String(s));
//            LED::setPreset(PresetType::SOLID);
//            LED::config(new CHSV(H->getVal() * 255 / 360, s, V->getVal() * 255 / 100));
//            LED::start();
        }
    }

    return true;
}


void HomeKit::init() {
    homeSpan.begin(Category::Lighting, "Fita LED");
    homeSpan.setLogLevel(1);

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
    FITA_LED::V->setVal(brightness * 100 / 255);

    if (brightness == 0) {
        FITA_LED::power->setVal(false);
    } else {
        FITA_LED::power->setVal(true);
    }
}