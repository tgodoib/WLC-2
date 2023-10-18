#ifndef WCL_2_PRESETS_H
#define WCL_2_PRESETS_H

#include "Preset.h"
#include <FastLED.h>
#include "infrastructure/RENDER.h"

class PFadeColor : public Preset {
private:
    unsigned short step;
    unsigned long lastUpdate;
    unsigned short duration;
    unsigned short steps;
    std::function<void()> done;

    Preset* to;
    CHSV from_arr[LED_COUNT];
    CHSV to_arr[LED_COUNT];
public:
    void start() override;
    void loop() override;
    Preset* config(void *p) override;
    void whenDone(std::function<void()> run);
};

class PFadeBrightness: public Preset {
private:
    unsigned short step;
    unsigned short steps;
    unsigned long lastUpdate;
    unsigned short duration;
    std::function<void()> done;

    PresetType lastPreset;

    uint8_t from;
    uint8_t to;

public:
    void start() override;
    void loop() override;
    Preset* config(void *p) override;
    void whenDone(std::function<void()> run);
};

class PSolid : public Preset {
private:
    CHSV color = CHSV(HUE_RED, 255, 255);
public:
    void start() override;

    void restoreData(char* data) override;

    Preset* config(void *p) override;
    CHSV getColor();
};


#endif //WCL_2_PRESETS_H
