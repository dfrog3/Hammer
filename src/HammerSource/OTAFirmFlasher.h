//
// Created by David Kaschub on 2021/07/31.
//

#ifndef HAMMER_OTAFIRMFLASHER_H
#define HAMMER_OTAFIRMFLASHER_H

#include <Arduino.h>
// Load Wi-Fi library
#include <WiFi.h>
#include <HammerSource/HammerDisplay.h>
#include <ArduinoOTA.h>


class OTAFirmFlasher {
public:
    OTAFirmFlasher &operator=(const OTAFirmFlasher &) = delete;

    static void Init(HammerDisplay *display, std::string ssid, std::string password);

    static void Update();
};


#endif //HAMMER_OTAFIRMFLASHER_H
