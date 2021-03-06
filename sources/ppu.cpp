#include "../includes/ppu.hpp"
#include <iostream>

Ppu::Ppu(Memory* t_memory): memory(t_memory), pixelInfoBuffer(160*144, {0, BG}){
    pixelFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGB888);
    RGBColor white = WHITE;
    uint32_t color = SDL_MapRGB(pixelFormat, white.r, white.g, white.b);
    RGBBuffer = std::vector<Uint32>(160*144,color);
}

void Ppu::renderLine(BYTE t_currentline){
    BYTE LCDcontrolRegister = getLCDControlRegister();
    //if bit 0 of FF40 is 1 then
    if(LCDcontrolRegister & 0x01){ // bit 0
        renderBGWindowLine(t_currentline);
    }
    else{
        RGBColor white = WHITE;
        uint32_t color = SDL_MapRGB(pixelFormat, white.r, white.g, white.b);
        RGBBuffer = std::vector<Uint32>(160*144,color);
    }
    
    //sprite enabled bit
    if(LCDcontrolRegister & 0x02){ //bit 1
        renderSpriteLine(t_currentline);
    }
}

pixel Ppu::toPixels(WORD t_lineOfTile, BYTE t_palette, bool flipX, int i){

    BYTE palette;
    //palette for sprite or bg
    switch(t_palette) {
        case 0:
            palette = getSpritePalette0();
            break;
        case 1:
            palette = getSpritePalette1();
            break;
        case 2:
            palette = getBGandWindowPalette();
            break;
        default:
            palette = getBGandWindowPalette();
    }

    BYTE data0 = t_lineOfTile & 0x00FF;
    BYTE data1 = t_lineOfTile >> 8;
    int k;

    k = (flipX) ? i : (7 - i);
    
    BYTE lsb = (data0 & (1 << k)) >> k;
    BYTE msb = (data1 & (1 << k)) >> k;
    BYTE b;
    //If is a sprite I have to change the bits (I do not why, but it works)
    if(t_palette < 2){
            b = (lsb<< 1) + msb;
    }
    else{       
        b  = (msb << 1) + lsb;
    }
    RGBColor rgb = getRGBColor(b, palette);

    //to keep the information about the current item on the screen
    sourceType type = (t_palette == 2) ? BG : SP;
    pixel p = {rgb, {b, type}};

    return p;
}

RGBColor Ppu::getRGBColor(BYTE t_colorID, BYTE palette) {
    RGBColor rgb;
    switch(t_colorID) {
        case 0:     //look at bit 1-0 of the tile palette
            palette &= 0x03;
            break;
        case 1:     //look at bit 3-2 of the tile palette
            palette &= 0x0C;
            //palette >>= 2;
            break;
        case 2:     //look at bit 5-4 of the tile palette
            palette &= 0x30;
            //palette >>= 4;
            break;
        case 3:     //look at bit 7-6 of the tile palette
            palette &= 0xC0;
            //palette >>= 6;
            break;
    }    

    palette >>= (t_colorID*2); 
    
    RGBColor color = getColorFromPaletteID(palette);
    return color;

}

RGBColor Ppu::getColorFromPaletteID(BYTE t_paletteID) {
    switch(t_paletteID) {
        case 0:      //white - 00
            return WHITE;
        case 1:     //light grey - 01
            return LIGHT_GREY;
        case 2:     //dark grey - 10
           return DARK_GREY;
        case 3:     //black - 11
           return BLACK;
        default:
            return BLACK;
    }     
}

void Ppu::fillLineOfTile(BYTE t_tileID, int i, BYTE t_currentline, sourceType t_type){ //type = 0 ->BG, type = 1 ->Sprite
    BYTE controlRegister = getLCDControlRegister();
    WORD lineOfATile;
    signed char signedTileID;
    WORD startAddress;
    WORD offset;

    //choose the correct memory zone
    if(controlRegister & 0x10){
        startAddress = 0x8000;
        offset = t_tileID*16;
    } else {
        startAddress = 0x8800;
        offset = ((signed char) t_tileID + 128)*16;
    }

    BYTE posY = getScrollY();
    BYTE posX = getScrollX();

    if(t_type == WN) {    //it is window
        posY = getWindowY();
        posX = getWindowX() - 7;
    }

    lineOfATile = memory->readWord(startAddress + ((posY + t_currentline)% 8)*2 + offset); //16B = tile dimension
    pixel p = toPixels(lineOfATile, 2, false, (i + posX)%8);
        
    int offsetTile =  t_currentline*160 + i;

    // write in the buffer
    if ((offsetTile >= 0 && offsetTile < (160*144))) {
        SDL_PixelFormat* pixelFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGB888);
        RGBBuffer[offsetTile] = SDL_MapRGB(pixelFormat, p.color.r, p.color.g, p.color.b);
        pixelInfoBuffer[offsetTile] = p.info;
    }
}

void Ppu::renderBGWindowLine(BYTE t_currentline){
    BYTE scrollY = getScrollY();
    BYTE scrollX = getScrollX();  
    BYTE LCDcontrolRegister = getLCDControlRegister();    
    WORD BGMemoryStart = LCDcontrolRegister & 0x08 ? 0x9C00 : 0x9800;
    
    BYTE tileID;
    WORD offset;

    BYTE windowY = getWindowY();
    BYTE windowX = (getWindowX() - 7);
    WORD windowMemoryStart = (LCDcontrolRegister & 0x40) ? 0x9C00 : 0x9800;

    for(int i = 0; i < SCREEN_WIDTH; ++i){ // for evey pixel
        if((LCDcontrolRegister & 0x20) && (t_currentline >= windowY) && (i >= windowX)){
            offset = (((BYTE)(t_currentline - windowY))/8)*32 + (((BYTE)(i - windowX))/8);
            tileID = memory->readByte(windowMemoryStart + offset);
            fillLineOfTile(tileID, i, t_currentline, WN);
            continue;        
        }
        offset = (((BYTE)(scrollY + t_currentline))/8)*32 + (((BYTE)(scrollX + i))/8);
        tileID = memory->readByte(BGMemoryStart + offset);
        fillLineOfTile(tileID, i, t_currentline, BG);
    }
}

//return sprite info
sprite Ppu::getSprite(BYTE spriteNum) {
    WORD spriteAddr = 0xFE00 + 4*spriteNum;
    sprite spriteInfo;
    spriteInfo.posY = (int)memory->readByte(spriteAddr++) - 16;
    spriteInfo.posX = (int)memory->readByte(spriteAddr++) - 8;
    spriteInfo.patternNum = memory->readByte(spriteAddr++);
    spriteInfo.attribs = memory->readByte(spriteAddr);
    return spriteInfo;    
}

pixel Ppu::getSpritePixel(sprite t_sprite, BYTE t_currentline, int j) {  

    pixel pixelOfASprite;
    WORD lineOfASprite;
    WORD spriteStartAddr = 0x8000 + 16*t_sprite.patternNum; //sprites ALWAYS start at 8000
    bool flipOnX = isFlippedX(t_sprite.attribs);
    bool flipOnY = isFlippedY(t_sprite.attribs);
    WORD offset;

    offset = t_currentline - t_sprite.posY;

    // sprite flipped on Y
    if (flipOnY){
        if(getLCDControlRegister() & 0x04) {offset = (15 - offset);}
        else {offset = (7 - offset);}
    }
    offset *= 2;
    
    lineOfASprite = (memory->readByte(spriteStartAddr + offset)<<8) + (memory->readByte(spriteStartAddr + offset + 1));
    pixelOfASprite = toPixels(lineOfASprite, getPaletteNum(t_sprite.attribs), flipOnX, j);
    return pixelOfASprite;
}

void Ppu::renderSpriteLine(BYTE t_currentline) {  
    pixel spritePixel;
    sprite spriteData;
    int spriteCount=0;    
    BYTE height;
  
    //for every sprite
    for(int i = 0; i < 40; ++i) {
        spriteData = Ppu::getSprite(i);
        getLCDControlRegister() & 0x04 ? height = 16: height = 8;  //sprite height (8x8 || 8x16)

        if((t_currentline >= spriteData.posY) && (t_currentline < spriteData.posY + height)) { // scanline is over a sprite
            if (spriteCount++ > 9) break; // Max 10 sprites per line
            for(int j = 0; j < 8; ++j) { // per pixel
                spritePixel = Ppu::getSpritePixel(spriteData, t_currentline, j);  
                int offset = (t_currentline)*160 + spriteData.posX + j;
                if (offset >= 0 && offset < (160*144) && checkBufferPriority(spriteData.attribs, spritePixel.info, pixelInfoBuffer[offset])) {
                        RGBBuffer[offset] = SDL_MapRGB(pixelFormat, spritePixel.color.r, spritePixel.color.g, spritePixel.color.b);
                        pixelInfoBuffer[offset] = spritePixel.info;
                }         
            }
        }            
    }
}


bool Ppu::checkBufferPriority(BYTE t_spriteAttrib, pixelInfo t_spriteInfoNew, pixelInfo t_pixelInfoOld) {
    //check sprite transparency
    if(t_spriteInfoNew.colorID == 0) {return false;}
    //sprite over BG and sprite is on top (priority = 0)
    if(t_pixelInfoOld.type == BG && isSpriteOnTop(t_spriteAttrib)) {return true;}
    else if(t_pixelInfoOld.type == BG && !isSpriteOnTop(t_spriteAttrib) && t_pixelInfoOld.colorID == 0) {return true;}
    //sprite over olds prite and new sprite is on top
    else if(t_pixelInfoOld.type == SP && (t_spriteInfoNew.colorID > t_pixelInfoOld.colorID) && isSpriteOnTop(t_spriteAttrib)) {return true;}
    else {return false;}
 
}