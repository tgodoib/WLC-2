#ifndef WCL_2_LED_H
#define WCL_2_LED_H

#include "presets/PresetType.h"
#include "presets/Preset.h"
#include <map>
#include <FastLED.h>
#include "infrastructure/LOG.h"
#include "controllers/DATA.h"

class LED {

private:
    static PresetType preset;
    static std::map<char*, PresetType> str2enum;
    static std::map<PresetType, Preset*> enum2Preset;

public:
    static void init();
    static void loop();

    static void setPreset(PresetType pt);
    static Preset* getPreset();

    static Preset* config(void *c);
    static Preset* start(bool fade = true);

    static void setBrightness(uint8_t v, bool fade = true);
    static uint8_t getBrightness();

    static void enableFade();
    static void disableFade();

};

#endif //WCL_2_LED_H
