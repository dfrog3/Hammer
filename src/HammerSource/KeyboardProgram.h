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
#include <algorithm>
#include <cctype>
#include <string>



class KeyboardProgram {


private:
    std::vector<HammerProfile> profiles;
    HammerProfile *activeProfile;
    RotaryWheel *rotaryWheel;
    HammerDisplay *hammerDisplay;
    bool hasReleasedStrike;
    int strike;
    int thumb;
    long canStrikeTime = 0;
    long eraseLastTurnTime;
    volatile int activeProfileIndex = 0;
private:
    void DrawNames();
    void PressButtons();
    void PressSpecialKeys(std::vector<std::string> keys);
public:
    KeyboardProgram(
            RotaryWheel *rotaryWheel,
            SdCardInterfacer *sdCardInterfacer,
            HammerDisplay *hammerDisplay,
            std::string settingsFileName,
            int strike, int thumb);

    KeyboardProgram &operator=(const KeyboardProgram &) = delete;


public:
    void OnWheelTurn(RotaryState state, int count);

    void Update();

};


#endif //HAMMER_KEYBOARDPROGRAM_H
