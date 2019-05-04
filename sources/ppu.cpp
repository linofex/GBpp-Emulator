#include "../includes/ppu.hpp"
#include <iostream>
#include <algorithm>

Ppu::Ppu(Memory* t_memory): memory(t_memory), pixelInfoBuffer(160*144, {0, BG}), RGBBuffer(160*144, BLACK){
}

void Ppu::renderLine(BYTE t_currentline){
    bufferY = t_currentline;
    BYTE LCDcontrolRegister = getLCDControlRegister();
    if(LCDcontrolRegister & 0x01){ // bit 0
        renderBGWindowLine(t_currentline);
        //std::cout<< "BG--------\n";
    }
    else{
        // std::cout<< "BBBBBB--------\n";
        RGBBuffer = std::vector<RGBColor>(160*144,WHITE);
    }
    
    if(LCDcontrolRegister & 0x20){ //bit 5
        //renderWindowLine(t_currentline);
        //std::cout<< "WINDOW\n";
    }
    if(LCDcontrolRegister & 0x02){ //bit 1
        renderSpriteLine(t_currentline);
        //std::cout<< "SPRITE";
    }
}

pixel Ppu::toPixels(WORD t_lineOfTile, BYTE t_palette, bool flipX, int i){

    BYTE palette;
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

    //for(int i = 0; i < 8; ++i) {
        // remember 7-1, otherwise tiles flip
        k = (flipX) ? i : (7 - i);
        
        BYTE lsb = (data0 & (1 << k)) >> k;
        BYTE msb = (data1 & (1 << k)) >> k;
        //RGBColor rgb = getRGBColor(((msb << 1) + lsb) >> 2*i);
        BYTE b = (msb << 1) + lsb;
        RGBColor rgb = getRGBColor(b, palette);

        //to keep the information about the current item on the screen
        sourceType type = (t_palette == 2) ? BG : SP;

        pixel p = {rgb, {b, type}};
    //}
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
  // std::cout<<" R:" << (int)color.r <<" G:" << (int)color.g <<" B:" << (int)color.b <<std::endl;
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

void Ppu::fillLineOfTile(BYTE t_tileID, int i, BYTE t_currentline, sourceType t_type){    //type = 0 -> BG, type = 1 -> Sprite
    BYTE controlRegister = getLCDControlRegister();
    WORD lineOfATile;
    signed char signedTileID;
    WORD startAddress;
    WORD offset;

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
        /* for(int k = 0 ; k< 8 ;++k){
            if(lineOfPixels.at(k).r == 255){
                std::cout << " ";
            }
            else {
                std::cout << "1 ";
            }
        } */
         //std::cout<< "\n\n";
        // std::cout << std::endl;
        //compute colors returns pixels
        // fill in buffer using counterline and i
        
        // //std::cout << (offset)<< " *";

        int offsetTile =  t_currentline*160 + i;
        RGBBuffer[offsetTile] = p.color;
        pixelInfoBuffer[offsetTile] = p.info;
        
            //bitmap for BG and sprites priority -> if BG is WHITE, sprite always on top (even if has no priority)
            //spritePixelPriority[offsetTile + l] = (lineOfPixels.at(l).r == 255) ? true : false;

      //  std::copy (lineOfPixels.begin(), lineOfPixels.begin() + lineOfPixels.size(), RGBBuffer.begin()+offsetTile);
       // std::cout<<" R:" << (int)RGBBuffer.at(h).r <<" G:" << (int)RGBBuffer.at(h).g <<" B:" << (int)RGBBuffer.at(h).b <<std::endl;
              
    //}
    // std::cout << std::endl;
    // for(int t = 0; t < 8; t++) {
    //      for(int k = 0 ; k< 8 ;++k){
    //         if((int)RGBBuffer.at(t*160 + k).r == 255){
    //             std::cout << "  ";
    //         }
    //         else
    //         {
    //             std::cout << "1 ";
    //         }
            
    //     }
    //     std::cout << std::endl;
    // }
    // std::cout << std::endl;
}

void Ppu::renderBGWindowLine(BYTE t_currentline){
    BYTE scrollY = getScrollY();// >> 3;
    BYTE scrollX = getScrollX();// >> 3;  
    BYTE LCDcontrolRegister = getLCDControlRegister();    
    WORD BGMemoryStart = LCDcontrolRegister & 0x08 ? 0x9C00 : 0x9800;
    
    BYTE tileID;
    WORD offset;

    BYTE windowY = getWindowY();
    BYTE windowX = (getWindowX() - 7);
    WORD windowMemoryStart = (LCDcontrolRegister & 0x40) ? 0x9C00 : 0x9800;

    for(int i = 0; i < SCREEN_WIDTH; ++i){
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

/* void Ppu::renderWindowLine(BYTE t_currentline){
    BYTE windowY = getWindowY() >> 3;
    BYTE windowX = (getWindowX() - 7) >> 3;
    BYTE windowMemoryStart = (getLCDControlRegister() & 0x40) ? 0x9C00 : 0x9800;
    BYTE tileID;
    BYTE offset;
    //std::cerr<<std::hex<<(int)(getWindowY())<<"\n";
    for(int i = 0; i < SCREEN_WIDTH/8; ++i){
        if((t_currentline >= windowY*8) && (i > windowX) && (i < 20)){ 
            offset = windowY*32 + (windowX + i);// % 32;
            tileID = memory->readByte(windowMemoryStart + offset);
            fillLineOfTile(tileID, i, t_currentline, 0);
        }
    }

} */

sprite Ppu::getSprite(BYTE spriteNum) {
    WORD spriteAddr = 0xFE00 + 4*spriteNum;
    sprite spriteInfo;
    spriteInfo.posY = memory->readByte(spriteAddr++);
    spriteInfo.posX = memory->readByte(spriteAddr++);
    spriteInfo.patternNum = memory->readByte(spriteAddr++);
    spriteInfo.attribs = memory->readByte(spriteAddr);
    //std::cout<<"PatNumb: "<<std::hex<<(int)spriteInfo.patternNum<<std::endl;
    //if(spriteInfo.patternNum == 0) {    
        //std::cout<<"PosY: "<<std::hex<<(int)spriteInfo.posY<<std::endl;
        //std::cout<<"PosX: "<<std::hex<<(int)spriteInfo.posX<<std::endl;
        //std::cout<<"PatNumb: "<<std::hex<<(int)spriteInfo.patternNum<<std::endl;
        //std::cout<<"Attribs: "<<std::hex<<(int)spriteInfo.attribs<<std::endl;
        //std::cout<<"__________________________________________"<<std::endl;
    //}

    return spriteInfo;    
}

pixel Ppu::getSpritePixel(sprite t_sprite, BYTE t_currentline, int j) {  
    BYTE height = 8;
    pixel pixelOfASprite;
    WORD lineOfASprite;
    WORD spriteStartAddr = 0x8000 + 16*t_sprite.patternNum;
    bool flipOnX = isFlippedX(t_sprite.attribs);
    bool flipOnY = isFlippedY(t_sprite.attribs);
    WORD offset;

    if(getLCDControlRegister() & 0x04) {    //sprite size is 8x16
        offset = (t_sprite.posY - t_currentline);
        if(!flipOnY) {
            offset = (16 - offset);
        }
    }   
    else{
        offset = t_currentline%8;
        if(flipOnY) {
        // std::cout << (int)t_sprite.patternNum << "   ";
            offset = (8 - offset);
        }
    }
     
    offset *= 2;
    lineOfASprite = (memory->readByte(spriteStartAddr + offset)<<8) + (memory->readByte(spriteStartAddr + offset + 1));
    pixelOfASprite = toPixels(lineOfASprite, getPaletteNum(t_sprite.attribs), flipOnX, j);

    return pixelOfASprite;
}

void Ppu::renderSpriteLine(BYTE t_currentline) {  
    pixel spritePixel;
    sprite spriteData;
    
    BYTE height = 8;
    //std::cout<<std::endl;   
    for(int i = 0; i < 40; ++i) {
        spriteData = Ppu::getSprite(i);
        //spritePixels = Ppu::buildSprite(spriteData)
        //std::cout<<std::hex<<(int)spriteData.patternNum<<"\t";
        if(getLCDControlRegister() & 0x04) {    //sprite size is 8x16
            height = 16;
        }

        int startY = (int)(spriteData.posY) - 16;
        int startX = (int)(spriteData.posX) - 8;     

        for(int j = 0; j < 8; ++j) {
            WORD offset = (t_currentline)*160 + startX + j;
            if((t_currentline >= startY) && (t_currentline < startY + height)) {
                spritePixel = Ppu::getSpritePixel(spriteData, t_currentline, j);  
            }
            else {
                break;
            }
 
            //check if the current scanline is inside the sprite (Y bounds)
            if((t_currentline >= startY) && (t_currentline < startY + height)) {
                if(checkBufferPriority(spriteData.attribs, spritePixel.info, pixelInfoBuffer[offset])) {
                //check if BG has priority on transparent pixels of the sprite
                //if((isSpriteOnTop(spriteInfo.attribs) || (!isSpriteOnTop(spriteInfo.attribs) && RGBBuffer[t_currentline*160 + startX + j].r == 252) && spritePixel.r != 252))  {
                    //(!isSpriteOnTop(spriteInfo.attribs) && spritePixelPriority[t_currentline*160 + startX + j])) {
                    //check if the new sprite has a higher color priority wrt the previous sprite drawn
                    //if(spritePixelsLine.at(j).r < RGBBuffer[t_currentline*160 + startX + j].r) {
                        pixelInfoBuffer[offset] = spritePixel.info;
                        RGBBuffer[offset] = spritePixel.color;

                        /*if(spriteData.patternNum == 0x22) {
                            std::cout<<"colorID: "<<std::hex<<(int)spritePixel.info.colorID<<std::endl;
                            std::cout<<"color: "<<std::hex<<(int)spritePixel.color.r<<std::endl;
                            //std::cout<<"palette: "<<std::hex<<(int)spriteData.attribs<<std::endl;
                        }*/
                
                    //}
                }            
            }
        }
    }
}

bool Ppu::checkBufferPriority(BYTE t_spriteAttrib, pixelInfo t_spriteInfoNew, pixelInfo t_spriteInfoOld) {
    //check sprite transparency
    if(t_spriteInfoNew.colorID == 0)
        return false;
    //sprite over BG and sprite is on top (priority = 0)
    if(t_spriteInfoOld.type == BG && isSpriteOnTop(t_spriteAttrib)) {
        return true;
    }
    else if(t_spriteInfoOld.type == BG && !isSpriteOnTop(t_spriteAttrib) && t_spriteInfoOld.colorID == 0) {
        return true;
    }
    //sprite over olds prite and new sprite is on top
    else if(t_spriteInfoOld.type == SP && (t_spriteInfoNew.colorID > t_spriteInfoOld.colorID)) {
        return true;
    }
    else {
        return false;
    }
 
}