#include "presets/Presets.h"

void PSolid::start() {
    RENDER::fill(getColor());
    RENDER::update();

    LOG::debug("PSolid start", String(getColor().v));
}

Preset* PSolid::config(void *p) {
    //TODO: Catch error on cast
    color = *((CHSV*) p);

    char data[3] = {(char)color.h, (char)color.s, (char)color.v};
    DATA::storePresetData(3, data);

    return this;
}

CHSV PSolid::getColor() {
    return color;
}

void PSolid::restoreData(char *data) {
    color = CHSV(data[0], data[1], data[2]);
}
