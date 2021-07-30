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
    SdCardInterfacer(HammerDisplay *pDisplay);


    SdCardInterfacer &operator=(const SdCardInterfacer &) = delete;

    void Init() ;

public:
    void listDir(fs::FS &fs, const char *dirname, uint8_t levels);

    void createDir(fs::FS &fs, const char *path) ;

    void removeDir(fs::FS &fs, const char *path) ;

    String readFile(const char *path) ;

    void writeFile(const char *path, const char *message) ;

    void appendFile(fs::FS &fs, const char *path, const char *message) ;

    void renameFile(fs::FS &fs, const char *path1, const char *path2) ;

    void deleteFile(fs::FS &fs, const char *path);

    void testFileIO(fs::FS &fs, const char *path) ;
};


#endif //FIRM_SDCARDINTERFACER_H
