#ifndef WCL_2_RENDER_H
#define WCL_2_RENDER_H

#include "../Env.h"
#include "../controllers/LED.h"
#include "../../.pio/libdeps/nodemcuv2/FastLED/src/FastLED.h"

class RENDER {
private:
    static CRGB led_arr_rgb[LED_COUNT];
    static CHSV led_arr[LED_COUNT];
    static bool disable_update;

    static uint8_t brightness;

public:
    static void init();
    static void update();

    static CHSV get(int i);
    static void set(int i, CHSV c);
    static void fill(CHSV c);

    static CHSV* getArr();

    static void setBrightness(uint8_t b, bool report = true);
    static uint8_t getBrightness();

    static void pause();
    static void resume();
};


#endif