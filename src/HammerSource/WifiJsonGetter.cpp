//
// Created by David Kaschub on 2021/07/30.
//

#include "WifiJsonGetter.h"

WiFiServer server(80);
MDNSResponder *responder = new MDNSResponder();

WifiJsonGetter::WifiJsonGetter(HammerDisplay *hammerDisplay, SdCardInterfacer *sdCardInterfacer,
                               std::string ssid,
                               std::string password,
                               std::string settings) {
    this->ssid = ssid;
    this->password = password;
    this->settings = settings;
    this->display = hammerDisplay;
    this->sdCardInterfacer = sdCardInterfacer;
    // Initialize the output variables as outputs

    // Connect to Wi-Fi network with SSID and password
    Serial.print("Connecting to ");
    WiFi.mode(WIFI_AP);                    // Changing ESP32 wifi mode to AccessPoint
    WiFi.softAP("Hammer");                    // Changing ESP32 wifi mode to AccessPoint
    display->WriteText("192.168.4.1 hammer");
    server.begin();
    responder->begin("hammer");

}

void WifiJsonGetter::Update() {
    WiFiClient client = server.available();

    if (client) {
        currentTime = millis();
        previousTime = currentTime;
        String currentLine = "";
        while (client.connected() && currentTime - previousTime <= timeoutTime) {
            currentTime = millis();
            if (client.available()) {
                char c = client.read();
                header += c;
                if (c == '\n') {
                    if (currentLine.length() == 0) {
                        SendResponse(client);
                        break;
                    } else {
                        currentLine = "";
                    }
                } else if (c != '\r') {
                    currentLine += c;
                }
            }
        }
        ProcessHeader();
        // Clear the header variable
        header = "";
        // Close the connection
        client.stop();
    }
}

std::string urlDecode(std::string str) {
    std::string ret;
    char ch;
    int i, ii, len = str.length();

    for (i = 0; i < len; i++) {
        if (str[i] != '%') {
            if (str[i] == '+')
                ret += ' ';
            else
                ret += str[i];
        } else {
            sscanf(str.substr(i + 1, 2).c_str(), "%x", &ii);
            ch = static_cast<char>(ii);
            ret += ch;
            i = i + 2;
        }
    }
    return ret;
}

void WifiJsonGetter::ProcessHeader() {
    std::string s = header.c_str();
    int start = s.find('=') + 1;
    int end = s.find('\n') - 25;

    std::string front = s.substr(0, start);
    std::string j = s.substr(start, end);
    j = urlDecode(j);

    bool isSettings = (front.find("settings") != std::string::npos);
    bool isSSID = (front.find("ssid") != std::string::npos);
    bool isPassword = (front.find("password") != std::string::npos);

    if (isSettings) {
        sdCardInterfacer->writeFile(settings.c_str(), j.c_str());
    }
    if (isSSID) {
        sdCardInterfacer->writeFile(ssid.c_str(), j.c_str());
    }
    if (isPassword) {
        sdCardInterfacer->writeFile(password.c_str(), j.c_str());
    }
}

void WifiJsonGetter::SendResponse(WiFiClient client) {
// HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
    // and a content-type so the client knows what's coming, then a blank line:
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println("Connection: close");
    client.println();

    // Display the HTML web page
    client.println("<!DOCTYPE html><html>");
    client.println(
            "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
    client.println("<link rel=\"icon\" href=\"data:,\">");
    // CSS to style the on/off buttons
    // Feel free to change the background-color and font-size attributes to fit your preferences
    client.println(
            "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
    client.println(
            ".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
    client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
    client.println(".button2 {background-color: #555555;}</style></head>");

    // Web Page Heading
    client.println("<body><h1>Hammer File Updater</h1>");

    // Display current state, and ON/OFF buttons for GPIO 26
    // If the output26State is off, it displays the ON button
    client.println(
            "<form method=\"get\"><input type=\"text\" name=\"settings\" size=\"30\"><p><input type=\"submit\" value=\"Settings\"></p></form>");
    client.println(
            "<form method=\"get\"><input type=\"text\" name=\"firmssid\" size=\"30\"><p><input type=\"submit\" value=\"SSID\"></p></form>");
    client.println(
            "<form method=\"get\"><input type=\"text\" name=\"firmpassword\" size=\"30\"><p><input type=\"submit\" value=\"Password\"></p></form>");

    client.println("</body></html>");

    // The HTTP response ends with another blank line
    client.println();
}
