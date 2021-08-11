#include <Arduino.h>
#include <HammerSource/HammerDisplay.h>
#include <HammerSource/SdCardInterfacer.h>
#include <HammerSource/RotaryWheel.h>
#include <HammerSource/KeyboardProgram.h>
#include <HammerSource/BootScreen.h>
// todo boot screen 1
// - mac pc flag


String ssid = "dhr01-d6a488-g";
String password = "23d71963b5465";

HammerDisplay *hammerDisplay;
SdCardInterfacer *sdCard;
RotaryWheel *rotaryWheel;
BootScreen *bootScreen;
KeyboardProgram *keyboardProgram;

int wheel1 = 34;
int wheel2 = 32;
int strike = 25;
int thumb = 27;
int macPc = 12;


const std::string ssidFile = "/ssid.txt";
const std::string passwordFile = "/password.txt";
const std::string settingsFile = "/settings.json";

std::function<void()> updateFunction = *new std::function<void()>([]() {});


void setup() {
//    Serial.begin(115200);


pinMode(strike, INPUT_PULLUP);
    pinMode(thumb, INPUT_PULLUP);
    pinMode(macPc, INPUT_PULLUP);
    delay(1000);
    hammerDisplay = new HammerDisplay();
    sdCard = new SdCardInterfacer(hammerDisplay);
    rotaryWheel = new RotaryWheel(wheel1, wheel2);

    sdCard->Init();
    ssid = sdCard->readFile(ssidFile.c_str());
    password = sdCard->readFile(passwordFile.c_str());



    if (digitalRead(thumb) == LOW) {
        bootScreen = new BootScreen(rotaryWheel, sdCard, hammerDisplay, strike, ssidFile.c_str(), passwordFile.c_str(),
                                    settingsFile.c_str());
        updateFunction = []() { bootScreen->Update(); };
    } else {
        hammerDisplay->WriteText("start");
        keyboardProgram = new KeyboardProgram(rotaryWheel, sdCard, hammerDisplay, settingsFile, strike, thumb);
        updateFunction = []() { keyboardProgram->Update(); };
        delay(1000);
    }


}


void loop() {
    updateFunction();
}