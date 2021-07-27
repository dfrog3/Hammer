//
// Created by David Kaschub on 2021/07/27.
//

#ifndef HAMMER_HAMMERBLUETOOTHUPLOADER_H
#define HAMMER_HAMMERBLUETOOTHUPLOADER_H
#include <BluetoothSerial.h>
#include <Arduino.h>


class HammerBlueToothUploader {
private:
//    BluetoothSerial SerialBT;


public:
    HammerBlueToothUploader &operator=(const HammerBlueToothUploader &) = delete;

    HammerBlueToothUploader();
    String Update();
};


#endif //HAMMER_HAMMERBLUETOOTHUPLOADER_H
