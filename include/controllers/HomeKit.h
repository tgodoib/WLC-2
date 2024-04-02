//
// Created by Tiago Bannwart on 01/04/24.
//

#ifndef WCL_2_HOMEKIT_H
#define WCL_2_HOMEKIT_H

#include <FastLED.h>
#include <HomeSpan.h>

struct FITA_LED : Service::LightBulb {
    static SpanCharacteristic *power;
    static SpanCharacteristic *brightness;
    static SpanCharacteristic *H;
    static SpanCharacteristic *S;
    static SpanCharacteristic *V;

    FITA_LED();

    boolean update() override;

};

class HomeKit {

public:
    static void init();
    static void loop();

    static void reportColor(CHSV *color);
    static void reportBrightness(uint8_t brightness);
};


#endif //WCL_2_HOMEKIT_H
