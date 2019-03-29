#ifndef LCD_H
#define LCD_H

#include "utility.hpp"

class Memory;
//class Gpu;

class Lcd {
    private:
        Memory* memory;
        //Gpu* gpu;

        unsigned char currentLine;
        unsigned short remainingCycles;

        void setLCDStatus(void);
        unsigned char getScanline(void);
        void setScanline(BYTE);
        bool testInterrupt(BYTE);
        bool testCoincidence(void);

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