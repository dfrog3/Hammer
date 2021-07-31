#include <Arduino.h>
#include <HammerSource/HammerDisplay.h>
#include <HammerSource/SdCardInterfacer.h>
#include <HammerSource/RotaryWheel.h>
#include <WiFi.h>
#include <HammerSource/WifiJsonGetter.h>
#include <HammerSource/OTAFirmFlasher.h>



String ssid = "dhr01-d6a488-g";
String password = "23d71963b5465";

bool staredInOTA;
HammerDisplay *hammerDisplay;
SdCardInterfacer *sdCard;
RotaryWheel *rotaryWheel;
WifiJsonGetter *jsonGetter;



int wheel1 = 34;
int wheel2 = 32;
int strike = 25;
int thumb = 27;
int macPc = 12;

int lastWheelState;
int wheelDirectionCount;

const std::string ssidFile ="/ssid.txt";
const std::string passwordFile = "/password.txt";
const std::string settingsFile = "/settings.json";

void setup() {
    pinMode(strike, INPUT_PULLUP);
    pinMode(thumb, INPUT_PULLUP);
    pinMode(macPc, INPUT_PULLUP);
    delay(1000);
    hammerDisplay = new HammerDisplay();
    sdCard = new SdCardInterfacer(hammerDisplay);
    sdCard->Init();
    ssid = sdCard->readFile(ssidFile.c_str());
    password = sdCard->readFile(passwordFile.c_str());
    staredInOTA = false;

    hammerDisplay->WriteText("reset?");
    delay(2000);
    bool hasHitThumb = false;
    unsigned long currentTime = millis();
    while (millis() < currentTime + 3000) {
        delay(500);
        hasHitThumb = hasHitThumb || (digitalRead(thumb) == LOW);
    }

    if (hasHitThumb) {
        OTAFirmFlasher::Init(hammerDisplay, ssid.c_str(), password.c_str());
        staredInOTA = true;
        return;
        // end ota
    } else {
        hammerDisplay->WriteText("start");
        rotaryWheel = new RotaryWheel(wheel1, wheel2);
        jsonGetter = new WifiJsonGetter(hammerDisplay, sdCard, ssidFile, passwordFile, settingsFile);
        delay(1000);
    }



//    Serial.begin(115200);
}


void loop() {
    if (staredInOTA) {
        OTAFirmFlasher::Update();
        return;
    }
    rotaryWheel->Update();
    jsonGetter->Update();


}