#ifndef PPU_H
#define PPU_H

#include "memory.hpp"

class Ppu{
    private:
        Memory* memory;
        std::vector<RGBColor> pixelBuffer;
        std::vector<RGBColor> customPalette;
        
        BYTE bufferY;

        
        inline BYTE getBGandWindowPalette(void) const {return memory->readByte(BGP);}   //Background palette 0xFF47
        inline BYTE getSpritePalette0(void) const {return memory->readByte(OBP0);}      //Object Palette spirtes0 0xFF48
        inline BYTE getSpritePalette1(void) const {return memory->readByte(OBP1);}      //Object Palette spirtes1 0xFF49
        inline BYTE getScrollX(void) const {return memory->readByte(SCROLLX);}
        inline BYTE getScrollY(void) const {return memory->readByte(SCROLLY);}
        inline BYTE getWindowX(void) const {return memory->readByte(WINDOWX);}
        inline BYTE getWindowY(void) const {return memory->readByte(WINDOWY);}
        inline BYTE getLCDControlRegister(void) const {return memory->readByte(LCDCONTROL);}

        void fillTile(BYTE, int, bool);
        void renderBGLine();
        void renderWindowLine();
        void renderSpriteLine();
        std::vector<RGBColor> toColors(WORD, bool);
        RGBColor getColorFromPaletteID(BYTE, bool);
        RGBColor getRGBColor(BYTE, bool);



    public:
        Ppu(Memory*);
        void renderLine(void);
        inline std::vector<RGBColor> getPixelBuffer(void) const {return pixelBuffer;}



};



#endif