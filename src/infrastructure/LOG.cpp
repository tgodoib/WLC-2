#include "infrastructure/LOG.h"

void LOG::init() {
    Serial.begin(115200);

    LOG::line();
    LOG::info("LOG", "Pronto.");
    LOG::line();
}

void LOG::loop() {

}

void LOG::line() {
    Serial.println("");
}

void LOG::info_nl(String prefix, String s) {
    sendMsg(s, prefix, "\u001b[36m");
}

void LOG::debug_nl(String prefix, String s) {
    sendMsg(s, prefix, "\u001b[33m");
}

void LOG::error_nl(String prefix, String s) {
    sendMsg(s, prefix, "\u001b[31m");
}

void LOG::info(String prefix, String s) {
    info_nl(prefix, s);
    line();
}

void LOG::debug(String prefix, String s) {
    debug_nl(prefix, s);
    line();
}

void LOG::error(String prefix, String s) {
    error_nl(prefix, s);
    line();
}

void LOG::sendMsg(String msg, String prefix, String colorCode) {
    Serial.print(colorCode);
    if (strlen(prefix.c_str()) != 0) Serial.print(String("[") + prefix + String("] "));
    Serial.print(msg + "\u001b[0m");
}