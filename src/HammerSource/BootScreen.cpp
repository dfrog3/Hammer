//
// Created by David Kaschub on 2021/08/01.
//

#include "BootScreen.h"

BootScreen::BootScreen(RotaryWheel *rotaryWheel, SdCardInterfacer *sdCardInterfacer, HammerDisplay *hammerDisplay,
                       int strike, String ssid, String password, String settings) {

    this->rotaryWheel = rotaryWheel;
    this->hammerDisplay = hammerDisplay;
    hammerDisplay->WriteText("INBOOT");
    delay(1000);
    hammerDisplay->WriteBiosMenu(0);
    activeProfileIndex = 0;
    this->strike = strike;
    rotaryWheel->SetTurnAction(
            new std::function<void(RotaryState, int)>(
                    [this](RotaryState direction, int count) { this->OnWheelTurn(direction, count); })
    );
    this->ssid = ssid;
    this->password = password;
    this->settings = settings;
    this->sdCardInterfacer = sdCardInterfacer;

}

void BootScreen::OnWheelTurn(RotaryState state, int count) {
    if (count > 3) {
        switch (state) {

            case Up:
                activeProfileIndex += 1;
                break;
            case Down:
                activeProfileIndex -= 1;
                break;
        }
        int size = 1;

        if (activeProfileIndex > size) {
            activeProfileIndex = 0;
        } else if (activeProfileIndex < 0) {
            activeProfileIndex = size;

        }

        hammerDisplay->WriteBiosMenu(activeProfileIndex);
        rotaryWheel->ResetCount();
    }
}

void BootScreen::Update() {
    if ((digitalRead(strike) == LOW) && !isFirm && !isConfig) {
        if (activeProfileIndex == 0) {
            isFirm = true;
            OTAFirmFlasher::Init(hammerDisplay,
                              sdCardInterfacer->readFile(ssid.c_str()).c_str(),
                              sdCardInterfacer->readFile(password.c_str()).c_str()
            );
        } else {
            isConfig = true;
            jsonGetter = new WifiJsonGetter(hammerDisplay, sdCardInterfacer, ssid.c_str(), password.c_str(),
                                            settings.c_str());
        }
    }
    if (isFirm) {
        OTAFirmFlasher::Update();
        return;
    }
    if (isConfig) {
        jsonGetter->Update();
        return;
    }
    rotaryWheel->Update();

}
