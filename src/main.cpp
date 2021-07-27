#include <Arduino.h>
#include <HammerSource/HammerDisplay.h>
#include <HammerSource/SdCardInterfacer.h>
#include <HammerSource/RotaryWheel.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <ArduinoOTA.h>
#include <HammerSource/HammerBlueToothUploader.h>
#include <BluetoothSerial.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

String ssid = "dhr01-d6a488-g";
String password = "23d71963b5465";

bool staredInOTA;
HammerDisplay *hammerDisplay;
SdCardInterfacer *sdCard;
RotaryWheel *rotaryWheel;
HammerBlueToothUploader *uploader;
BluetoothSerial SerialBT;


int wheel1 = 34;
int wheel2 = 32;
int strike = 25;
int thumb = 27;
int macPc = 12;

int lastWheelState;
int wheelDirectionCount;


void setup() {
    pinMode(strike, INPUT_PULLUP);
    pinMode(thumb, INPUT_PULLUP);
    pinMode(macPc, INPUT_PULLUP);
    delay(1000);
    hammerDisplay = new HammerDisplay();
    sdCard = new SdCardInterfacer(hammerDisplay);
    sdCard->Init();
    ssid = sdCard->readFile("/ssid.txt");
    password = sdCard->readFile("/password.txt");
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
        hammerDisplay->WriteText("resetting");

        staredInOTA = true;
        WiFi.mode(WIFI_STA);
        WiFi.begin(ssid.c_str(), password.c_str());
        while (WiFi.waitForConnectResult() != WL_CONNECTED) {
            hammerDisplay->WriteText("bad wifi");
            delay(5000);
            ESP.restart();
        }

        ArduinoOTA
                .onStart([]() {
                    String type;
                    if (ArduinoOTA.getCommand() == U_FLASH)
                        type = "sketch";
                    else // U_SPIFFS
                        type = "filesystem";

                    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
                    hammerDisplay->WriteText("Found firm");
                })
                .onEnd([]() {
                    hammerDisplay->WriteText("\nEnd");
                })
                .onProgress([](unsigned int progress, unsigned int total) {
                })
                .onError([](ota_error_t error) {
//                hammerDisplay->WriteText(("Error[%u]: ", error));
                    hammerDisplay->WriteText(("Error OTA"));
                    if (error == OTA_AUTH_ERROR) hammerDisplay->WriteText("Auth Failed");
                    else if (error == OTA_BEGIN_ERROR) hammerDisplay->WriteText("Begin Failed");
                    else if (error == OTA_CONNECT_ERROR) hammerDisplay->WriteText("Connect Failed");
                    else if (error == OTA_RECEIVE_ERROR) hammerDisplay->WriteText("Receive Failed");
                    else if (error == OTA_END_ERROR) hammerDisplay->WriteText("End Failed");
                });

        ArduinoOTA.begin();

        hammerDisplay->WriteText(WiFi.localIP().toString());
        return;
        // end ota
    } else {
        hammerDisplay->WriteText("start");
        delay(1000);
    }


    rotaryWheel = new RotaryWheel(wheel1, wheel2);
    uploader = new HammerBlueToothUploader();
    Serial.begin(115200);
    SerialBT.begin("ESP");
}


void loop() {
    if (staredInOTA) {
        ArduinoOTA.handle();
        return;
    }
    rotaryWheel->Update();

    String val = SerialBT.readString();
    if(val != ""){
        hammerDisplay->WriteText(val);
        delay(3000);
    }


}