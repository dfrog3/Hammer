//
// Created by David Kaschub on 2021/07/11.
//

#ifndef HAMMER_HAMMERDISPLAY_H
#define HAMMER_HAMMERDISPLAY_H


#include <Arduino.h>
#include "RotaryWheel.h"
#include "HammerSource/HammerProfile.h"

class HammerDisplay {
    HammerDisplay &operator=(const HammerDisplay &) = delete;

private:
    bool savedDisplay[32][128];

public:
    HammerDisplay();

    void WriteText(String txt);

    void WriteBool(bool v);

    void WriteRotaryState(RotaryState state);

    void DrawFrame();

    void DrawKeys(HammerProfile *profile);

    void DrawMotionBar(float percentComplete, bool direction);

    void DrawProfileNames(int mode, std::string names[6]);

    void WriteBiosMenu(int i);

    void Hide();

    void Show();
};


#endif //HAMMER_HAMMERDISPLAY_H
