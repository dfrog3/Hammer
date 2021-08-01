//
// Created by David Kaschub on 2021/07/12.
//

#ifndef HAMMER_ROTARYWHEEL_H
#define HAMMER_ROTARYWHEEL_H

#include <Arduino.h>
#include <queue>
#include <functional>

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
    volatile int lastState = -1;
    volatile RotaryState lastRegisteredState;
    volatile int directionCount;
    unsigned long lastDirectionTime;
    std::deque<WheelEvent> *eventQ;
    const int timeBetweenWipes = 300;
    unsigned long  lastWipe;
    unsigned long  lastLastWipe;

    std::function<void(RotaryState, int)> turnFunction = *new std::function<void(RotaryState, int)>([](RotaryState direction, int count) { });


    void RegisterTurn(RotaryState state);
    void UpdateReset();

public:
    RotaryWheel(int pin1, int pint2);

    RotaryWheel &operator=(const RotaryWheel &) = delete;

    void Update();
    void SetTurnAction(std::function<void(RotaryState, int)> *function);

    unsigned long getLastDirectionTime() const;


    void ResetCount();
};


#endif //HAMMER_ROTARYWHEEL_H
