#include <Arduino.h>
#include <HammerSource/HammerDisplay.h>
#include <HammerSource/SdCardInterfacer.h>
#include <HammerSource/RotaryWheel.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>


const char *ssid = "dhr01-d6a488-g";
const char *password = "23d71963b5465";

bool staredInOTA;
HammerDisplay *hammerDisplay;
SdCardInterfacer *sdCard;
RotaryWheel *rotaryWheel;


int wheel1 = 34;
int wheel2 = 32;
int strike = 25;
int thumb = 27;
int macPc = 12;

void UpdateWheel(){
    int state = rotaryWheel->Update();

    switch (state) {

        case Up:
            Serial.println("up");
            break;
        case Down:
            Serial.println("Down");
            break;
        case Nothing:
            break;
    }
}
void setup() {
    pinMode(strike, INPUT_PULLUP);
    pinMode(thumb, INPUT_PULLUP);
    pinMode(macPc, INPUT_PULLUP);

    delay(1000);
    hammerDisplay = new HammerDisplay();
    staredInOTA = false;

    hammerDisplay->WriteText("reset?");
    delay(2000);
    bool hasHitThumb = false;
    while (millis() < 6000) {
        hammerDisplay->WriteBool(digitalRead(thumb) == HIGH);
        delay(500);
        hasHitThumb = hasHitThumb || (digitalRead(thumb) == LOW);
    }

    if (hasHitThumb) {
        hammerDisplay->WriteText("resetting");

        staredInOTA = true;
        WiFi.mode(WIFI_STA);
        WiFi.begin(ssid, password);
        while (WiFi.waitForConnectResult() != WL_CONNECTED) {
            hammerDisplay->WriteText("bad wifi");
            delay(5000);
            ESP.restart();
        }

        // Port defaults to 3232
        // ArduinoOTA.setPort(3232);

        // Hostname defaults to esp3232-[MAC]
        // ArduinoOTA.setHostname("myesp32");

        // No authentication by default
        // ArduinoOTA.setPassword("admin");

        // Password can be set with it's md5 value as well
        // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
        // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

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
//                hammerDisplay->WriteText("Progress: %u%%\r", (progress / (total / 100)));
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

//        hammerDisplay->WriteText("rdy 4 upld");
        hammerDisplay->WriteText(WiFi.localIP().toString());
        return;
        // end ota
    } else {
        hammerDisplay->WriteText("start ok");
        delay(2000);
    }

    sdCard = new SdCardInterfacer(hammerDisplay);
    sdCard->Init();
    rotaryWheel = new RotaryWheel(wheel1, wheel2);
    Serial.begin(115200);
    attachInterrupt(digitalPinToInterrupt(wheel1), UpdateWheel, CHANGE);
    attachInterrupt(digitalPinToInterrupt(wheel2), UpdateWheel, CHANGE);


}



void loop() {
    if (staredInOTA) {
        ArduinoOTA.handle();
        return;
    }


}