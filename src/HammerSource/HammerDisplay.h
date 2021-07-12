//
// Created by David Kaschub on 2021/07/11.
//

#ifndef HAMMER_HAMMERDISPLAY_H
#define HAMMER_HAMMERDISPLAY_H


#include <Arduino.h>
#include "RotaryWheel.h"

class HammerDisplay {
    HammerDisplay &operator=(const HammerDisplay &) = delete;

public:
    HammerDisplay();

    void WriteText(String txt);

    void WriteBool(bool v);

    void WriteRotaryState(RotaryState state);
};


#endif //HAMMER_HAMMERDISPLAY_H
