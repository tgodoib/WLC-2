#include "presets/Presets.h"

Preset *PFadeColor::config(void *p) {
    to = (Preset *) p;
    return this;
}

void PFadeColor::start() {
    duration = 1500;
    steps = 150;

    std::copy(RENDER::getArr(), RENDER::getArr() + LED_COUNT, from_arr);
    RENDER::pause();

    uint8_t tempBrightness = RENDER::getBrightness();
    RENDER::setBrightness(255);

    to->start();
    to->loop();

    std::copy(RENDER::getArr(), RENDER::getArr() + LED_COUNT, to_arr);
    RENDER::setBrightness(tempBrightness);

    RENDER::resume();

    lastUpdate = millis();
    step = 0;
}

void PFadeColor::loop() {
    if (step > steps) {
        done();
        return;
    }

    if (millis() - lastUpdate < duration / steps) return;
    lastUpdate = millis();

    for (int i = 0; i < LED_COUNT; ++i) {
        uint8_t h = from_arr[i].h + (to_arr[i].h - from_arr[i].h) * step / steps;
        uint8_t s = from_arr[i].s + (to_arr[i].s - from_arr[i].s) * step / steps;
        uint8_t v = from_arr[i].v + (to_arr[i].v - from_arr[i].v) * step / steps;
        RENDER::set(i, CHSV(h, s, v));
    }
    step++;
//    delay(50);
    RENDER::update();
}

void PFadeColor::whenDone(std::function<void()> run) {
    done = run;
}

