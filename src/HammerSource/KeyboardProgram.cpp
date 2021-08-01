//
// Created by David Kaschub on 2021/08/01.
//

#include "KeyboardProgram.h"

BleKeyboard bleKeyboard;


KeyboardProgram::KeyboardProgram(
        RotaryWheel *rotaryWheel,
        SdCardInterfacer *sdCardInterfacer,
        HammerDisplay *hammerDisplay,
        std::string settingsFileName,
        int strike, int thumb) {
    this->strike = strike;
    this->thumb = thumb;
    std::string rawSettings = sdCardInterfacer->readFile(settingsFileName.c_str()).c_str();

    cJSON *settings = cJSON_Parse(rawSettings.c_str());
    std::vector<cJSON> rawProfiles{0};

    rawProfiles.clear();
    int count = cJSON_GetArraySize(settings);
    for (int i = 0; i < count; ++i) {
        rawProfiles.push_back(*cJSON_GetArrayItem(settings, i));

    }

    profiles.clear();

    for (cJSON r : rawProfiles) {
        profiles.push_back(*new HammerProfile(&r));
    }
    activeProfile = &profiles[0];

    this->hammerDisplay = hammerDisplay;
    this->rotaryWheel = rotaryWheel;

    rotaryWheel->SetTurnAction(
            new std::function<void(RotaryState, int)>(
                    [this](RotaryState direction, int count) { this->OnWheelTurn(direction, count); })
    );

    rotaryWheel->ResetCount();
    hammerDisplay->DrawFrame();
    DrawNames();
    hammerDisplay->DrawKeys(activeProfile);

    hammerDisplay->DrawMotionBar(0, false);

    bleKeyboard.deviceName = "Hammer";
    bleKeyboard.begin();


}

void KeyboardProgram::DrawNames() {
    std::string names[profiles.size()];
    for (int i = 0; i < profiles.size(); ++i) {
        names[i] = profiles[i].getName();
    }
    hammerDisplay->DrawProfileNames(activeProfileIndex, names);
}

void KeyboardProgram::OnWheelTurn(RotaryState state, int count) {
    eraseLastTurnTime = millis() + 2000;//time until reset scroll wheel
    if (count > 3) {
        switch (state) {

            case Up:
                activeProfileIndex += 1;
                break;
            case Down:
                activeProfileIndex -= 1;
                break;
        }
        int size = profiles.size() - 1;

        if (activeProfileIndex > size) {
            activeProfileIndex = 0;
        } else if (activeProfileIndex < 0) {
            activeProfileIndex = size;

        }

        activeProfile = &profiles[activeProfileIndex];

        DrawNames();
        hammerDisplay->DrawKeys(activeProfile);
        rotaryWheel->ResetCount();
        count = 0;
    }

    hammerDisplay->DrawMotionBar(((float) count) / 3, state == RotaryState::Up);


}

void KeyboardProgram::Update() {
    rotaryWheel->Update();
    PressButtons();
    if (millis() > eraseLastTurnTime) {
        rotaryWheel->ResetCount();
        hammerDisplay->DrawMotionBar(0, true);

    }


}

void KeyboardProgram::PressSpecialKeys(std::vector<std::string> keys){
    if (HammerProfile::ContainsApple(keys)) {
        bleKeyboard.press(KEY_LEFT_GUI);
    }
    if (HammerProfile::ContainsShift(keys)) {
        bleKeyboard.press(KEY_LEFT_SHIFT);
    }
    if (HammerProfile::ContainsControl(keys)) {
        bleKeyboard.press(KEY_LEFT_CTRL);
    }
    if (HammerProfile::ContainsOption(keys)) {
        bleKeyboard.press(KEY_LEFT_ALT);
    }
    if (HammerProfile::ContainsEnter(keys)) {
        bleKeyboard.press(KEY_RETURN);
    }
    if (HammerProfile::ContainsTab(keys)) {
        bleKeyboard.press(KEY_TAB);
    }
    if (HammerProfile::ContainsEsc(keys)) {
        bleKeyboard.press(KEY_ESC);
    }
}



void KeyboardProgram::PressButtons() {
    bool struck = (digitalRead(strike) == LOW);
    if (struck) {

        if (!hasReleasedStrike) {
            return;
        }
        hasReleasedStrike = false;
        canStrikeTime = millis() + 500;//time between strikes
        if (digitalRead(thumb) == LOW) {
            PressSpecialKeys(activeProfile->getThumbSpecialKeys());
            for (const auto &i : activeProfile->getThumbChars()) {
                bleKeyboard.press(std::tolower(i[0]));
            }

        } else {
            PressSpecialKeys(activeProfile->getStrikeSpecialKeys());
            for (const auto &i : activeProfile->getStrikeChars()) {
                bleKeyboard.press(std::tolower(i[0]));
            }
        }
        delay(50);
        bleKeyboard.releaseAll();
    } else {
        if (millis() > canStrikeTime) {

            hasReleasedStrike = true;
        }
    }


}
