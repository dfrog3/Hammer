//
// Created by David Kaschub on 2021/07/30.
//

#ifndef HAMMER_WIFIJSONGETTER_H
#define HAMMER_WIFIJSONGETTER_H

#include <Arduino.h>
// Load Wi-Fi library
#include <WiFi.h>
#include <HammerSource/HammerDisplay.h>
#include <HammerSource/SdCardInterfacer.h>
#include "ESPmDNS.h"


class WifiJsonGetter {
private:
    HammerDisplay *display;
    SdCardInterfacer *sdCardInterfacer;
    String header;

// Current time
    unsigned long currentTime = millis();
// Previous time
    unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
    const long timeoutTime = 2000;
    std::string ssid;
    std::string password;
    std::string settings;

    void ProcessHeader();

    static void SendResponse(WiFiClient client);

public:

    WifiJsonGetter(HammerDisplay *hammerDisplay, SdCardInterfacer *sdCardInterfacer,
                   std::string ssid,
                   std::string password,
                   std::string settings);
    WifiJsonGetter &operator=(const WifiJsonGetter &) = delete;

    void Update();
};


#endif //HAMMER_WIFIJSONGETTER_H
