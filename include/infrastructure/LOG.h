#ifndef WCL_2_LOG_H
#define WCL_2_LOG_H

#include "Arduino.h"

class LOG {
public:
    static void init();
    static void loop();

    static void line();
    static void info_nl(String p, String s);
    static void debug_nl(String p, String s);
    static void error_nl(String p, String s);
    static void info(String p, String s);
    static void debug(String p, String s);
    static void error(String p, String s);

private:
    static void sendMsg(String msg, String prefix, String colorCode);
};

#endif //WCL_2_LOG_H
