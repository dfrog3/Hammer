//
// Created by David Kaschub on 2021/07/12.
//

#include "RotaryWheel.h"

RotaryWheel::RotaryWheel(int pin1, int pin2) {
    pinMode(pin1, INPUT_PULLDOWN);
    pinMode(pin2, INPUT_PULLDOWN);
    this->pin1 = pin1;
    this->pin2 = pin2;
    this->eventQ = new std::deque<WheelEvent>();
    this->eventQ->push_back(WheelEvent(RotaryState::Nothing, 0));
    this->eventQ->push_back(WheelEvent(RotaryState::Nothing, 0));
}

RotaryState RotaryWheel::Update() {


    delay(5);
    bool pin1bool = digitalRead(pin1) == LOW;
    bool pin2bool = digitalRead(pin2) == LOW;
    int state = -1;
    RotaryState action = RotaryState::Nothing;
    if (pin1bool == false && pin2bool == false) {
        state = 0;
    } else if (pin1bool == true && pin2bool == false) {
        state = 1;
    } else if (pin1bool == true && pin2bool == true) {
        state = 2;
    } else if (pin1bool == false && pin2bool == true) {
        state = 3;
    }

    if (lastState == -1 || lastState == state) {
        lastState = state;
        return RotaryState::Nothing;
    }

    if (lastState == 3 && state == 0) {
        lastState = state;
        action = RotaryState::Up;
    } else if (state == 3 && lastState == 0) {
        lastState = state;
        action = RotaryState::Down;
    } else if (state > lastState) {
        lastState = state;
        action = RotaryState::Up;
    } else if (state < lastState) {
        lastState = state;
        action = RotaryState::Down;
    }


    lastState = state;
    if (action != RotaryState::Nothing) {
        eventQ->pop_front();

        eventQ->push_back(WheelEvent(action, millis()));

        WheelEvent w1 = eventQ->at(0);
        WheelEvent w2 = eventQ->at(1);

        if (w1.getState() == w2.getState() && w2.getMills() - w1.getMills() < 200) {
            return w1.getState();
        }
    }
    return RotaryState::Nothing;


}

void RotaryWheel::UpdateReset() {

    if (lastWipe < lastLastWipe) {
        lastWipe = 0;
        lastLastWipe = 0;
    }
    if (millis() > lastWipe + timeBetweenWipes) {
        noInterrupts();
        this->eventQ = new std::deque<WheelEvent>();
        this->eventQ->push_back(WheelEvent(RotaryState::Nothing, 0));
        this->eventQ->push_back(WheelEvent(RotaryState::Nothing, 0));
        interrupts();
        lastLastWipe = lastWipe;
        lastWipe = millis();
    }

}


WheelEvent::WheelEvent(RotaryState state, unsigned long mills) {
    this->state = state;
    this->mills = mills;
}

unsigned long WheelEvent::getMills() const {
    return mills;
}

RotaryState WheelEvent::getState() const {
    return state;
}
