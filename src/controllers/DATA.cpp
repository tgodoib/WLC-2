#include "controllers/DATA.h"

//0: Verify byte
//1: Brightness value
//2: Preset value

void DATA::init() {
    EEPROM.begin(8);
    LOG::info("DATA", "Initialized.");
}

void DATA::reset() {
    EEPROM.writeByte(0, 0);
    EEPROM.commit();
}

void DATA::set(int i, char val) {
    EEPROM.writeChar(0, 'A');
    EEPROM.writeChar(i, val);
    EEPROM.commit();
}

char DATA::get(int i) {
    return EEPROM.read(i);
}

void DATA::storePreset(PresetType p) {
    set(2, p < 2 ? 2 : p);
}

PresetType DATA::getPreset() {
    if (get(0) != 'A') return PresetType::SOLID;
    return (PresetType) get(2);
}

void DATA::storePresetData(int size, char *data) {
    if (size > 5) {
        LOG::error("DATA", "Cannot store more than 5 bytes!");
        return;
    }

    for (int i = 0; i < size; ++i) {
        set(i + 3, data[i]);
    }
}

void DATA::getPresetData(int size, char *data) {
    for (int i = 0; i < size; ++i) {
        data[i] = get(i + 3);
    }
}

void DATA::storeBrightness(uint8_t b) {
    EEPROM.writeByte(1, b);
    EEPROM.commit();
}

uint8_t DATA::getBrightness() {
    if (get(0) != 'A') return 255;
    return get(1);
}
