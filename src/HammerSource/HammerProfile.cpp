//
// Created by David Kaschub on 2021/07/31.
//

#include "HammerProfile.h"

HammerProfile::HammerProfile(cJSON *profile) {
//bleKeyboard.press(KEY_RIGHT_GUI) //apple
    this->strikeDisplay = cJSON_GetStringValue(cJSON_GetObjectItem(profile, "strikeDisplay"));
    this->thumbDisplay = cJSON_GetStringValue(cJSON_GetObjectItem(profile, "thumbDisplay"));
    this->name = cJSON_GetStringValue(cJSON_GetObjectItem(profile, "name"));


    strikeChars = UnpackJson(cJSON_GetObjectItem(profile, "strikeChars"));
    strikeSpecialKeys = UnpackJson(cJSON_GetObjectItem(profile, "strikeSpecialKeys"));
    thumbChars = UnpackJson(cJSON_GetObjectItem(profile, "thumbChars"));
    thumbSpecialKeys = UnpackJson(cJSON_GetObjectItem(profile, "thumbSpecialKeys"));

}

const std::string &HammerProfile::getStrikeDisplay() const {
    return strikeDisplay;
}

const std::vector<std::string> &HammerProfile::getStrikeChars() const {
    return strikeChars;
}

const std::vector<std::string> &HammerProfile::getStrikeSpecialKeys() const {
    return strikeSpecialKeys;
}

const std::string &HammerProfile::getThumbDisplay() const {
    return thumbDisplay;
}

const std::vector<std::string> &HammerProfile::getThumbChars() const {
    return thumbChars;
}

const std::vector<std::string> &HammerProfile::getThumbSpecialKeys() const {
    return thumbSpecialKeys;
}



std::vector<std::string> HammerProfile::UnpackJson(cJSON *json) {
    int count = cJSON_GetArraySize(json);
    std::vector<std::string> ret;
    ret.clear();
    for (int i = 0; i < count; ++i) {
        ret.push_back(cJSON_GetStringValue(cJSON_GetArrayItem(json, i)));

    }
    return ret;


}

bool ContainsKey(std::string key, std::vector<std::string> keys){
    return std::find(keys.begin(), keys.end(), key) != keys.end();
}

bool HammerProfile::ContainsApple(std::vector<std::string> keys) {
    return ContainsKey("apple", keys);
}

bool HammerProfile::ContainsControl(std::vector<std::string> keys) {
    return ContainsKey("control", keys);
}

bool HammerProfile::ContainsShift(std::vector<std::string> keys) {
    return ContainsKey("shift", keys);
}

bool HammerProfile::ContainsOption(std::vector<std::string> keys) {
    return ContainsKey("option", keys);
}

const std::string &HammerProfile::getName() const {
    return name;
}
