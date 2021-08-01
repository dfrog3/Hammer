//
// Created by David Kaschub on 2021/07/31.
//

#ifndef HAMMER_HAMMERPROFILE_H
#define HAMMER_HAMMERPROFILE_H

#include <cJSON.h>
#include <string>
#include <algorithm>
#include <vector>


class HammerProfile {
private:
    std::string strikeDisplay;
    std::string name;
    std::vector<std::string> strikeChars;
    std::vector<std::string> strikeSpecialKeys;
    std::string thumbDisplay;
    std::vector<std::string> thumbChars;
    std::vector<std::string> thumbSpecialKeys;


public:
    HammerProfile(cJSON *profile);
    HammerProfile &operator=(const HammerProfile &) = delete;

    static std::vector<std::string> UnpackJson(cJSON *json);
    static bool ContainsApple(std::vector<std::string> keys);
    static bool ContainsControl(std::vector<std::string> keys);
    static bool ContainsShift(std::vector<std::string> keys);
    static bool ContainsOption(std::vector<std::string> keys);

    const std::string &getStrikeDisplay() const;

    const std::vector<std::string> &getStrikeChars() const;

    const std::vector<std::string> &getStrikeSpecialKeys() const;

    const std::string &getThumbDisplay() const;

    const std::vector<std::string> &getThumbChars() const;

    const std::vector<std::string> &getThumbSpecialKeys() const;

    const std::string &getName() const;
};


#endif //HAMMER_HAMMERPROFILE_H
