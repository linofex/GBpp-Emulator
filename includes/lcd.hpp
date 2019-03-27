#ifndef LCD_H
#define LCD_H

#define LCDCONTROL  0xFF40
#define LCDSTATUS   0xFF41
#define LCDLY       0xFF44
#define LCDLYC      0xFF45

#define MODE0 0x00
#define MODE1 0x01
#define MODE2 0x10
#define MODE3 0x11

#include "utility.hpp"

class Memory;
//class Gpu;

class Lcd {
    private:
        Memory* mem;
        //Gpu* gpu;

        unsigned char currentLine;
        unsigned short remainingCycles;

        void setLCDStatus(void);
        unsigned char getScanline(void);
        void setScanline(BYTE);
        bool testInterrupt(BYTE);

    public:
        Lcd(void);
        Lcd(Memory* /*, Gpu* */);

        bool isLCDEnabled(void);
        BYTE getLCDMode(void);
        void setLCDMode(BYTE);
        BYTE getLCDModeRegister(void);
        void lcdStep(int);


    
};

#endif