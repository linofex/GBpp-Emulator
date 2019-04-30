#ifndef PPU_H
#define PPU_H

#include "memory.hpp"

class Ppu{
    private:
        Memory* memory;
        std::vector<bool> spritePixelPriority;
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
        inline bool isSpriteOnTop(BYTE t_attribs) {return ((t_attribs & 0x80) >> 7) == 0;}
        inline bool isFlippedX(BYTE t_attribs) {return (t_attribs & 0x20) >> 5;}
        inline bool isFlippedY(BYTE t_attribs) {return (t_attribs & 0x40) >> 6;}
        inline BYTE getPaletteNum(BYTE t_attribs) {return ((t_attribs & 0x10) >> 4);}

        void fillLineOfTile(BYTE, int, BYTE, bool);
        void renderBGLine(BYTE);
        void renderWindowLine(BYTE);
        void renderSpriteLine(BYTE);
        
        std::vector<RGBColor> toPixels(WORD, BYTE, bool);
        RGBColor getColorFromPaletteID(BYTE);
        RGBColor getRGBColor(BYTE, BYTE);
        sprite getSprite(BYTE);
        std::vector<std::vector<RGBColor>> buildSprite(sprite);
        std::vector<RGBColor> getSpritePixelLine(sprite, BYTE);
        //std::vector<RGBColor> flipY(std::vector<RGBColor>);

    public:
        Ppu(Memory*);
        void renderLine(BYTE);
        inline std::vector<RGBColor> getRGBBuffer(void) const {return RGBBuffer;}
        void fillLineOfTileDB(WORD);


};



#endif