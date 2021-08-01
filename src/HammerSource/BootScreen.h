//
// Created by David Kaschub on 2021/08/01.
//

#ifndef HAMMER_BOOTSCREEN_H
#define HAMMER_BOOTSCREEN_H


#include <HammerSource/RotaryWheel.h>
#include <HammerSource/SdCardInterfacer.h>
#include <HammerSource/OTAFirmFlasher.h>
#include <HammerSource/WifiJsonGetter.h>

class BootScreen {
public:
    BootScreen(RotaryWheel *rotaryWheel, SdCardInterfacer *sdCardInterfacer, HammerDisplay *hammerDisplay,
               int strike, String ssid, String password, String settings);

    BootScreen &operator=(const BootScreen &) = delete;

    void Update();

private:
    void OnWheelTurn(RotaryState state, int count);

    bool isFirm = false;
    bool isConfig = false;
    int strike;
    RotaryWheel *rotaryWheel;
    HammerDisplay *hammerDisplay;
    WifiJsonGetter *jsonGetter;
    SdCardInterfacer *sdCardInterfacer;
    int activeProfileIndex;
    String ssid;
    String password;
    String settings;
};


#endif //HAMMER_BOOTSCREEN_H
