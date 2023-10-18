#include "infrastructure/RENDER.h"

CRGB RENDER::led_arr_rgb[LED_COUNT];
CHSV RENDER::led_arr[LED_COUNT];
bool RENDER::disable_update = false;
uint8_t RENDER::brightness = 255;

void RENDER::init() {
    FastLED.addLeds<WS2812B, 2, GRB>(led_arr_rgb, LED_COUNT);
}

void RENDER::update() {
    if (!disable_update) {
        LOG::debug("RENDER", String(getBrightness()));
        LOG::debug("render v", String(led_arr[0].v));


        hsv2rgb_rainbow(led_arr, led_arr_rgb, LED_COUNT);
        nscale8_video(led_arr_rgb, LED_COUNT, getBrightness());
        FastLED.show();
    }
}

CHSV RENDER::get(int i) {
    return led_arr[i];
}

void RENDER::set(int i, CHSV c) {
    led_arr[i] = c;
}

void RENDER::fill(CHSV c) {
    LOG::debug("fill", String(c.s));
    fill_solid(led_arr, LED_COUNT, c);
}

CHSV* RENDER::getArr() {
    return led_arr;
}

void RENDER::setBrightness(uint8_t b) {
//    LOG::debug("RENDER", "setting brightness " + String(b));
    brightness = b;
//    FastLED.setBrightness(b);
}

uint8_t RENDER::getBrightness() {
    return brightness;
}

void RENDER::pause() {
    disable_update = true;
}

void RENDER::resume() {
    disable_update = false;
}
