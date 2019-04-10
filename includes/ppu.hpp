#ifndef PPU_H
#define PPU_H

#include "memory.hpp"

class Ppu{
    private:
        Memory* memory;
        std::vector<bool> pixelPriority;
        std::vector<RGBColor> RGBBuffer;
        
        
        BYTE bufferY;
     
        inline BYTE getBGandWindowPalette(void) const {return memory->readByte(BGP);}   //Background palette 0xFF47
        inline BYTE getSpritePalette0(void) const {return memory->readByte(OBP0);}      //Object Palette spirtes0 0xFF48
        inline BYTE getSpritePalette1(void) const {return memory->readByte(OBP1);}      //Object Palette spirtes1 0xFF49
        inline BYTE getScrollX(void) const {return memory->readByte(SCROLLX);}
        inline BYTE getScrollY(void) const {return memory->readByte(SCROLLY);}
        inline BYTE getWindowX(void) const {return memory->readByte(WINDOWX);}
        inline BYTE getWindowY(void) const {return memory->readByte(WINDOWY);}
        inline BYTE getLCDControlRegister(void) const {return memory->readByte(LCDCONTROL);}

        void fillLineOfTile(BYTE, int, BYTE, bool);
        void renderBGLine(BYTE);
        void renderWindowLine();
        void renderSpriteLine();
        std::vector<RGBColor> toPixels(WORD);
        RGBColor getColorFromPaletteID(BYTE);
        RGBColor getRGBColor(BYTE);



    public:
        Ppu(Memory*);
        void renderLine(BYTE);
        inline std::vector<RGBColor> getRGBBuffer(void) const {return RGBBuffer;}



};



#endif