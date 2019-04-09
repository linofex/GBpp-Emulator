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

std::vector<RGBColor> Ppu::toColors(WORD t_lineOfTile){}

void Ppu::fillTile(BYTE t_tileID, int i){
    BYTE controlRegister = getLCDControlRegister();
    WORD lineOfATile;
    signed char signedTileID;
    int countline = 0;
    if(controlRegister & 0x10){
        for(int j = 0; j< 8 ; j+= 2){
            //one line of the tile
            lineOfATile = memory->readWord(0x8000 + j);
            std::vector<RGBColor> lineOfPixels = toColors(lineOfATile);
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
        fillTile(tileID, i);
    }
    bufferY %= 140;
    // increase scrollX e scrollY? quando? secondo me no va fatt noi
    
     

}