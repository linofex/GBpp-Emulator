#ifndef LCD_H
#define LCD_H

#include "utility.hpp"

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

class Memory;
class Ppu;

class Lcd {
    private:
        Memory* memory;
        Ppu* ppu;
        signed short MODE_cycles;
     

        void setLCDStatus(void);
        unsigned char getScanline(void);
        void setScanline(BYTE);
        bool testInterrupt(BYTE);
        bool testCoincidence(void);
        bool isLCDEnabled(void);
        BYTE getLCDMode(void);
        void setLCDMode(BYTE);
        BYTE getLCDModeRegister(void);

    public:
        Lcd(void);
        Lcd(Memory*, Ppu*);
        void step(int);
        void renderScreen(SDL_Renderer*, SDL_Texture*);


    
};

#endif