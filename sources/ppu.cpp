#include "../includes/ppu.hpp"

Ppu::Ppu(Memory* t_memory): memory(t_memory), pixelBuffer(160*144){
    bufferY = 0;
    customPalette.push_back({255, 255, 255}); //00 = white
    customPalette.push_back({214, 214, 214}); //01 = light grey
    customPalette.push_back({64, 64, 64});    //10 = darkgrey
    customPalette.push_back({0, 0, 0});       //11 = black
}
void Ppu::renderLine(){
    BYTE LCDcontrolRegister = getLCDControlRegister();
    if(LCDcontrolRegister & 0x01){ // bit 0
        renderBGLine();
    }
    if(LCDcontrolRegister & 0x20){ //bit 5
        renderWindowLine();
    }
    if(LCDcontrolRegister & 0x02){ //bit 1
        renderSpriteLine();
    }
}

std::vector<RGBColor> Ppu::toColors(WORD t_lineOfTile, bool type){
    BYTE data0 = t_lineOfTile & 0x00FF;
    BYTE data1 = t_lineOfTile >> 8;

    std::vector<RGBColor> pixelsInTileLine;

    for(int i = 0; i < 8; ++i) {
        BYTE lsb = (data0 & (1 << i)) >> i;
        BYTE msb = (data1 & (1 << i)) >> i;
        //RGBColor rgb = getRGBColor(((msb << 1) + lsb) >> 2*i);
        RGBColor rgb = getRGBColor(((msb << 1) + lsb), type);
        pixelsInTileLine.push_back(rgb);
    }
    
    return pixelsInTileLine;
}

RGBColor Ppu::getRGBColor(BYTE t_colorID, bool type) {
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
    palette >>= t_colorID*2;
    
    return getColorFromPaletteID(palette, type);
}

RGBColor Ppu::getColorFromPaletteID(BYTE t_paletteID, bool type) {
    RGBColor rgb;
    switch(t_paletteID) {
        case 0:     //white - 00
            rgb = {255, 255, 255, type};
            break;
        case 1:     //light grey - 01
            rgb = {224, 224, 224, type};
            break;
        case 2:     //dark grey - 10
            rgb = {192, 192, 192, type};
            break;
        case 3:     //black - 11
            rgb = {0, 0, 0, type};
            break;
    }     
    return rgb;
}

void Ppu::fillTile(BYTE t_tileID, int i, bool type){    //type = 0 -> BG, type = 1 -> Sprite
    BYTE controlRegister = getLCDControlRegister();
    WORD lineOfATile;
    signed char signedTileID;
    int countline = 0;
    if(controlRegister & 0x10){
        for(int j = 0; j< 8 ; j+= 2){
            //one line of the tile
            lineOfATile = memory->readWord(0x8000 + j + t_tileID);
            std::vector<RGBColor> lineOfPixels = toColors(lineOfATile, type);
            //compute colors returns pixels
            // fill in buffer using counterline and i
            BYTE offset = (bufferY + countline)*160 + i*8;
            std::copy (lineOfPixels.begin(), lineOfPixels.end(), pixelBuffer.begin()+offset);
            countline ++;

        }

    }



}

void Ppu::renderBGLine(){
    BYTE scrollY = getScrollY() >> 3;
    BYTE scrollX = getScrollX() >> 3;
    BYTE BGMemoryStart = getLCDControlRegister() & 0x08 ? 0x9C00 : 0x9800;
    BYTE tileID;
    BYTE offset ;
    for(int i = 0; i < SCREEN_WIDTH/8  ; ++i){
        offset = scrollX*32 + (scrollY + i) % 32;
        tileID = memory->readByte(BGMemoryStart + offset);
        fillTile(tileID, i, 0);
    }
    bufferY %= 140;
    // increase scrollX e scrollY? quando? secondo me no va fatt noi

}