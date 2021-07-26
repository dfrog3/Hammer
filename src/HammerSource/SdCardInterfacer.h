//
// Created by David Kaschub on 2021/06/19.
//

#ifndef FIRM_SDCARDINTERFACER_H
#define FIRM_SDCARDINTERFACER_H

#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "HammerDisplay.h"


class SdCardInterfacer {
private:
    HammerDisplay *display;
public:
    SdCardInterfacer(HammerDisplay *pDisplay) {
        this->display = pDisplay;

    };


    SdCardInterfacer &operator=(const SdCardInterfacer &) = delete;

    void Init() {
        if (!SD.begin(2)) {
            display->WriteText("No SD card");
            return;
        }
        display->WriteText("SD OK");
        uint8_t cardType = SD.cardType();

//        if (cardType == CARD_NONE) {
//            display->WriteText("No SD card attached");
//            return;
//        }

//        Serial.print("SD Card Type: ");
//        if (cardType == CARD_MMC) {
//            Serial.println("MMC");
//        } else if (cardType == CARD_SD) {
//            Serial.println("SDSC");
//        } else if (cardType == CARD_SDHC) {
//            Serial.println("SDHC");
//        } else {
//            Serial.println("UNKNOWN");
//        }

//        uint64_t cardSize = SD.cardSize() / (1024 * 1024);
//        Serial.printf("SD Card Size: %lluMB\n", cardSize);

//        listDir(SD, "/", 0);
//        createDir(SD, "/mydir");
//        listDir(SD, "/", 0);
//        removeDir(SD, "/mydir");
//        listDir(SD, "/", 2);
//        writeFile(SD, "/hello.txt", "Hello ");
//        appendFile(SD, "/hello.txt", "World!\n");
//        readFile(SD, "/hello.txt");
//        deleteFile(SD, "/foo.txt");
//        renameFile(SD, "/hello.txt", "/foo.txt");
//        readFile(SD, "/foo.txt");
//        testFileIO(SD, "/test.txt");
//        Serial.printf("Total space: %lluMB\n", SD.totalBytes() / (1024 * 1024));
//        Serial.printf("Used space: %lluMB\n", SD.usedBytes() / (1024 * 1024));
    }

public:
    void listDir(fs::FS &fs, const char *dirname, uint8_t levels) {
//        Serial.printf("Listing directory: %s\n", dirname);

        File root = fs.open(dirname);
        if (!root) {
            display->WriteText("Failed to open directory");
            return;
        }
        delay(1000);
        if (!root.isDirectory()) {
            display->WriteText("not directory");
            return;
        }
        delay(1000);

        File file = root.openNextFile();
        while (file) {
            if (file.isDirectory()) {
                display->WriteText(file.name());
                delay(1000);

                if (levels) {
                    listDir(fs, file.name(), levels - 1);
                }
            } else {
                display->WriteText(file.name());
                delay(1000);
//                Serial.print("  FILE: ");
//                Serial.print(file.name());
//                Serial.print("  SIZE: ");
//                Serial.println(file.size());
            }
            file = root.openNextFile();
        }
    }

    void createDir(fs::FS &fs, const char *path) {
        return;

        Serial.printf("Creating Dir: %s\n", path);
        if (fs.mkdir(path)) {
            Serial.println("Dir created");
        } else {
            Serial.println("mkdir failed");
        }
    }

    void removeDir(fs::FS &fs, const char *path) {
        Serial.printf("Removing Dir: %s\n", path);
        if (fs.rmdir(path)) {
            Serial.println("Dir removed");
        } else {
            Serial.println("rmdir failed");
        }
    }

    String readFile(const char *path) {
//        return;

        display->WriteText(path);

        File file = SD.open(path);
        if (!file) {
            display->WriteText("Failed to open file for reading");
            return "";
        }

        String finalString = "";
        while (file.available()) {
            finalString += (char) file.read();
        }
        file.close();
        return finalString;
    }

    void writeFile(const char *path, const char *message) {


        File file = SD.open(path, FILE_WRITE);
        if (!file) {
            display->WriteText("Failed to open file for writing");
            return;
        }
        if (file.print(message)) {
            display->WriteText("File written");
        } else {
            display->WriteText("Write failed");
        }
        file.close();
    }

    void appendFile(fs::FS &fs, const char *path, const char *message) {
        return;

        Serial.printf("Appending to file: %s\n", path);

        File file = fs.open(path, FILE_APPEND);
        if (!file) {
            Serial.println("Failed to open file for appending");
            return;
        }
        if (file.print(message)) {
            Serial.println("Message appended");
        } else {
            Serial.println("Append failed");
        }
        file.close();
    }

    void renameFile(fs::FS &fs, const char *path1, const char *path2) {
        return;

        Serial.printf("Renaming file %s to %s\n", path1, path2);
        if (fs.rename(path1, path2)) {
            Serial.println("File renamed");
        } else {
            Serial.println("Rename failed");
        }
    }

    void deleteFile(fs::FS &fs, const char *path) {
        return;

        Serial.printf("Deleting file: %s\n", path);
        if (fs.remove(path)) {
            Serial.println("File deleted");
        } else {
            Serial.println("Delete failed");
        }
    }

    void testFileIO(fs::FS &fs, const char *path) {
        return;

        File file = fs.open(path);
        static uint8_t buf[512];
        size_t len = 0;
        uint32_t start = millis();
        uint32_t end = start;
        if (file) {
            len = file.size();
            size_t flen = len;
            start = millis();
            while (len) {
                size_t toRead = len;
                if (toRead > 512) {
                    toRead = 512;
                }
                file.read(buf, toRead);
                len -= toRead;
            }
            end = millis() - start;
            Serial.printf("%u bytes read for %u ms\n", flen, end);
            file.close();
        } else {
            Serial.println("Failed to open file for reading");
        }


        file = fs.open(path, FILE_WRITE);
        if (!file) {
            Serial.println("Failed to open file for writing");
            return;
        }

        size_t i;
        start = millis();
        for (i = 0; i < 2048; i++) {
            file.write(buf, 512);
        }
        end = millis() - start;
        Serial.printf("%u bytes written for %u ms\n", 2048 * 512, end);
        file.close();
    }
};


#endif //FIRM_SDCARDINTERFACER_H
