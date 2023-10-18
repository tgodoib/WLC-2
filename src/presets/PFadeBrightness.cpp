#include "presets/Presets.h"


Preset *PFadeBrightness::config(void *p) {
    to = *((uint8_t*) p);
    return this;
}

void PFadeBrightness::start() {
    duration = 750;
    steps = 75;

    from = RENDER::getBrightness();

    lastUpdate = millis();
    step = 0;
    LOG::debug("PFadeBrightness", "finished start");
}

void PFadeBrightness::loop() {

    if (step > steps) {
        LOG::debug("PFadeBrightness", "calling done");
        done();
        return;
    }

    if (millis() - lastUpdate < duration / steps) return;
    lastUpdate = millis();

//    LOG::debug("PFadeBrightness", "looping");

    RENDER::setBrightness(from + (to - from) * step / steps);
    RENDER::update();
    step++;
}

void PFadeBrightness::whenDone(std::function<void()> run) {
    done = run;
}
