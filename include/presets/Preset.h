#ifndef WCL_2_PRESET_H
#define WCL_2_PRESET_H

class Preset {

public:
    virtual Preset *config(void *p) { return nullptr; }

    virtual void start() {}
    virtual void loop() {}

    virtual void restoreData(char* data) {}
};

#endif //WCL_2_PRESET_H
