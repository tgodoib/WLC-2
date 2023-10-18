
#include "presets/Preset.h"
#include "controllers/LED.h"
#include "presets/Presets.h"

PresetType LED::preset;
std::map<char *, PresetType> LED::str2enum;
std::map<PresetType, Preset *> LED::enum2Preset;

void LED::init() {
    enum2Preset[PresetType::SOLID] = new PSolid();
    enum2Preset[PresetType::FADE_COLOR] = new PFadeColor();
    enum2Preset[PresetType::FADE_BRIGHTNESS] = new PFadeBrightness();
}

void LED::loop() {
    enum2Preset.at(preset)->loop();
}

void LED::setPreset(PresetType pt) {
    preset = pt;
    DATA::storePreset(pt);
}

Preset* LED::config(void *conf) {
    return enum2Preset.at(preset)->config(conf);
}

Preset *LED::start(bool fade) {
    PresetType pt = preset;
    if (fade) {
        preset = PresetType::FADE_COLOR;
        PFadeColor *pFade = (PFadeColor *) enum2Preset.at(preset)->config(enum2Preset.at(pt));
        pFade->whenDone([pt]() {
            preset = pt;
            enum2Preset.at(pt)->start();
        });
        pFade->start();
    } else {
        enum2Preset.at(preset)->start();
    }

    return enum2Preset.at(preset);
}

Preset *LED::getPreset() {
    return enum2Preset.at(preset);
}

void LED::setBrightness(uint8_t v, bool fade) {
    DATA::storeBrightness(v);
    if (fade) {
        PresetType pt = preset;
        LED::setPreset(PresetType::FADE_BRIGHTNESS);
        PFadeBrightness *pFade = (PFadeBrightness *) LED::config((uint8_t*) &v);
        pFade->whenDone([pt]() {
            LED::setPreset(pt);
        });
        pFade->start();
    } else {
        RENDER::setBrightness(v);
    }
}

uint8_t LED::getBrightness() {
    return RENDER::getBrightness();
}
