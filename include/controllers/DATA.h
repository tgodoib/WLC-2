#ifndef WCL_2_DATA_H
#define WCL_2_DATA_H

#include <EEPROM.h>
#include "presets/PresetType.h"
#include "presets/Presets.h"

class DATA {
public:
    static void init();
    static void reset();

    static void storePreset(PresetType p);
    static PresetType getPreset();

    static void storePresetData(int size, char* data);
    static void getPresetData(int size, char* data);

    static void storeBrightness(uint8_t b);
    static uint8_t getBrightness();

private:
    static void set(int i, char val);
    static char get(int i);
};


#endif //WCL_2_DATA_H
