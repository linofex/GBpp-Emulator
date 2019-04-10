#include "../includes/ppu.hpp"
#include <iostream>
Ppu::Ppu(Memory* t_memory): memory(t_memory), pixelPriority(160*144,0), RGBBuffer(160*144){
    bufferY = 0;
}
void Ppu::renderLine(BYTE t_currentline){
    bufferY = t_currentline;
    BYTE LCDcontrolRegister = getLCDControlRegister();
    //if(!(LCDcontrolRegister & 0x01)){ // bit 0
        renderBGLine(t_currentline);
        //std::cout<< "BG\n";
    //}
    if(LCDcontrolRegister & 0x20){ //bit 5
      //  renderWindowLine();
        //std::cout<< "WINDOW\n";
    }
    if(LCDcontrolRegister & 0x02){ //bit 1
        renderSpriteLine();
        //std::cout<< "SPRITE";
    }
    std::cout<< "############################# " << (int)bufferY << std::endl;
    // /bufferY = (++bufferY)%140;
}

std::vector<RGBColor> Ppu::toPixels(WORD t_lineOfTile){
    BYTE data0 = t_lineOfTile & 0x00FF;
    BYTE data1 = t_lineOfTile >> 8;

    std::vector<RGBColor> pixelsInTileLine;

    for(int i = 0; i < 8; ++i) {
        BYTE lsb = (data0 & (1 << i)) >> i;
        BYTE msb = (data1 & (1 << i)) >> i;
        //RGBColor rgb = getRGBColor(((msb << 1) + lsb) >> 2*i);
        RGBColor rgb = getRGBColor((msb << 1) + lsb);
        pixelsInTileLine.push_back(rgb);
    }
    return pixelsInTileLine;
}

RGBColor Ppu::getRGBColor(BYTE t_colorID) {
    BYTE palette = getBGandWindowPalette();
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
   // //std::cout <<(int) getScrollY()<<" "<<(int) bufferY<<" R:" << (int)color.r <<" G:" << (int)color.g <<" B:" << (int)color.b <<std::endl;
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
    }     
}

void Ppu::fillTile(BYTE t_tileID, int i, bool t_type){    //type = 0 -> BG, type = 1 -> Sprite
    BYTE controlRegister = getLCDControlRegister();
    WORD lineOfATile;
    signed char signedTileID;
    int countline = 0;
    WORD startAddress;
    BYTE offset;

    if(controlRegister & 0x10){
        startAddress = 0x8000;
        offset = t_tileID*16;
    } else {
        startAddress = 0x8800;
        offset = ((signed char) t_tileID + 127)*16;
    }

    for(int j = 0; j < 16 ; j+= 2){
        //one line of the tile
        lineOfATile = memory->readWord(startAddress + j + offset); //16B = tile dimension
        std::vector<RGBColor> lineOfPixels = toPixels(lineOfATile);
        //compute colors returns pixels
        // fill in buffer using counterline and i
        int offset = (bufferY + countline)*160 + i*8;
       // //std::cout << (offset)<< " *";
        std::copy (lineOfPixels.begin(), lineOfPixels.end(), RGBBuffer.begin()+offset);
        countline ++;
    }
}

void Ppu::renderBGLine(BYTE t_currentline){

    // CI VUOLE ANCHE LA SCANLINEEEE
    BYTE scrollY = getScrollY() >> 3;
    BYTE scrollX = getScrollX() >> 3;     
    BYTE BGMemoryStart = getLCDControlRegister() & 0x08 ? 0x9C00 : 0x9800;
    BYTE tileID;
    BYTE offset;
    for(int i = 0; i < SCREEN_WIDTH/8  ; ++i){
        offset = scrollX*32 + (scrollY + t_currentline/8  + i) % 32;
        tileID = memory->readByte(BGMemoryStart + offset);
        fillTile(tileID, i, 0);
    }

    // increase scrollX e scrollY? quando? secondo me no va fatt noi

}

void Ppu::renderWindowLine(){
    BYTE windowY = getWindowY() >> 3;
    BYTE windowX = (getWindowX() - 7) >> 3;
    BYTE windowMemoryStart = getLCDControlRegister() & 0x40 ? 0x9C00 : 0x9800;
    BYTE tileID;
    BYTE offset;
    for(int i = 0; i < SCREEN_WIDTH/8  ; ++i){
        offset = windowX*32 + (windowY + i) % 32;
        tileID = memory->readByte(windowMemoryStart + offset);
        fillTile(tileID, i, 0);
    }

}

void Ppu::renderSpriteLine(){



}