//
// Created by David Kaschub on 2021/07/12.
//

#ifndef HAMMER_ROTARYWHEEL_H
#define HAMMER_ROTARYWHEEL_H

#include <Arduino.h>
#include <queue>

enum RotaryState {
    Up = 0,
    Down = 1,
    Nothing = 3
};

struct WheelEvent {
private:
    RotaryState state;
    unsigned long  mills;
public:
    unsigned long  getMills() const;

    RotaryState getState() const;

    WheelEvent(RotaryState state, unsigned long  mills);
};

class RotaryWheel {
private:
    int pin1;
    int pin2;
    int lastState = -1;
    std::deque<WheelEvent> *eventQ;
    const int timeBetweenWipes = 300;
    unsigned long  lastWipe;
    unsigned long  lastLastWipe;
public:
    RotaryWheel(int pin1, int pint2);

    RotaryWheel &operator=(const RotaryWheel &) = delete;

    RotaryState Update();


};


#endif //HAMMER_ROTARYWHEEL_H
