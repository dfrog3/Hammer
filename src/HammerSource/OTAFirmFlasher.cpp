//
// Created by David Kaschub on 2021/07/31.
//

#include "OTAFirmFlasher.h"

void OTAFirmFlasher::Init(HammerDisplay *display, std::string ssid, std::string password) {

    display->WriteText("resetting");

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid.c_str(), password.c_str());
    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
        display->WriteText("bad wifi");
        delay(5000);
        ESP.restart();
    }

    ArduinoOTA
            .onStart([display]() {
                String type;
                if (ArduinoOTA.getCommand() == U_FLASH)
                    type = "sketch";
                else // U_SPIFFS
                    type = "filesystem";

                // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
                display->WriteText("Found firm");
            })
            .onEnd([display]() {
               display->WriteText("\nEnd");
            })
            .onProgress([display](unsigned int progress, unsigned int total) {
            })
            .onError([display](ota_error_t error) {
                //                display->WriteText(("Error[%u]: ", error));
                display->WriteText(("Error OTA"));
                if (error == OTA_AUTH_ERROR) display->WriteText("Auth Failed");
                else if (error == OTA_BEGIN_ERROR) display->WriteText("Begin Failed");
                else if (error == OTA_CONNECT_ERROR) display->WriteText("Connect Failed");
                else if (error == OTA_RECEIVE_ERROR) display->WriteText("Receive Failed");
                else if (error == OTA_END_ERROR) display->WriteText("End Failed");
            });

    ArduinoOTA.begin();

    display->WriteText(WiFi.localIP().toString());
}

void OTAFirmFlasher::Update() {
    ArduinoOTA.handle();
}
