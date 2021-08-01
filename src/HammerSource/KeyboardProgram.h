//
// Created by David Kaschub on 2021/08/01.
//

#ifndef HAMMER_KEYBOARDPROGRAM_H
#define HAMMER_KEYBOARDPROGRAM_H

#include "HammerProfile.h"
#include <cJSON.h>
#include <string>
#include <vector>
#include <ESP32-BLE-Keyboard-master/BleKeyboard.h>
#include <HammerSource/SdCardInterfacer.h>
#include <HammerSource/RotaryWheel.h>
#include <HammerSource/HammerDisplay.h>



class KeyboardProgram {


private:
//    BleKeyboard bleKeyboard;
    std::vector<HammerProfile> profiles;
    HammerProfile *activeProfile;
    RotaryWheel *rotaryWheel;
    HammerDisplay *hammerDisplay;
//    ulong lastTurn;
//    const unsigned long timeUntilReset = 2000;
    volatile int activeProfileIndex = 0;
private:
    void DrawNames();
public:
    KeyboardProgram(
            RotaryWheel *rotaryWheel,
            SdCardInterfacer *sdCardInterfacer,
            HammerDisplay *hammerDisplay,
            std::string settingsFileName);

    KeyboardProgram &operator=(const KeyboardProgram &) = delete;


public:
    void OnWheelTurn(RotaryState state, int count);

    void Update();

};


#endif //HAMMER_KEYBOARDPROGRAM_H
