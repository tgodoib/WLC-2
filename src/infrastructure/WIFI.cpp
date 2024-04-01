#include "infrastructure/WIFI.h"
#include <WiFi.h>
#include "infrastructure/LOG.h"

void WIFI::connect() {
    WiFi.hostname("WFC-2");
    WiFi.mode(WIFI_STA);
    WiFi.begin("Cabernet", "littleraven971");

    LOG::info("WIFI", "Conectando ao Wifi");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    LOG::line();
    LOG::info("WIFI", "Conectado a rede: " + WiFi.SSID());
    LOG::info("WIFI", "IP: " + WiFi.localIP().toString());
    LOG::line();
}