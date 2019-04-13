#include "../includes/ppu.hpp"
#include <iostream>
Ppu::Ppu(Memory* t_memory): memory(t_memory), pixelPriority(160*144,0), RGBBuffer(160*144,{0,0,0}){
    bufferY = 0;
}
void Ppu::renderLine(BYTE t_currentline){
    bufferY = t_currentline;
    BYTE LCDcontrolRegister = getLCDControlRegister();
    //if(LCDcontrolRegister & 0x01){ // bit 0
        renderBGLine(t_currentline);
        //std::cout<< "BG--------\n";
    //}
    //else{
        // std::cout<< "BBBBBB--------\n";
      //  RGBBuffer = std::vector<RGBColor>(160*144,{255,255,255});
    //}
    
    if(LCDcontrolRegister & 0x20){ //bit 5
       // renderWindowLine();
        //std::cout<< "WINDOW\n";
    }
    if(LCDcontrolRegister & 0x02){ //bit 1
        renderSpriteLine();
        //std::cout<< "SPRITE";
    }
    int a = 0;
   // std::cout<< "############################# " << (int)(a+ bufferY) << std::endl;
    // /bufferY = (++bufferY)%140;
}

std::vector<RGBColor> Ppu::toPixels(WORD t_lineOfTile){
    BYTE data0 = t_lineOfTile & 0x00FF;
    BYTE data1 = t_lineOfTile >> 8;

    std::vector<RGBColor> pixelsInTileLine;

    for(int i = 0; i < 8; ++i) {
        // remeber 8-1, otherwise tiles flip
        BYTE lsb = (data0 & (1 << (7-i))) >> (7-i);
        BYTE msb = (data1 & (1 << (7-i))) >> (7-i);
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

void Ppu::fillLineOfTile(BYTE t_tileID, int i, BYTE t_currentline, bool t_type){    //type = 0 -> BG, type = 1 -> Sprite
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
        offset = ((signed char) t_tileID + 127)*16;
    }
    //std::vector<WORD> tile = {0X0000, 0X3c3c, 0X6666 ,0X6666 ,0X6666 ,0X6666,0X3c3c, 0X0000};

    //for(int j = 0; j < 16 ; j+= 2){
        //one line of the tile
        //lineOfATile = tile.back();
        //tile.pop_back();
        lineOfATile = memory->readWord(startAddress + (t_currentline % 8)*2 + offset); //16B = tile dimension
        std::vector<RGBColor> lineOfPixels = toPixels(lineOfATile);
        // for(int k = 0 ; k< 8 ;++k){
        //     if(lineOfPixels.at(k).r == 255){
        //         std::cout << " ";
        //     }
        //     else
        //     {
        //         std::cout << "1 ";
        //     }
            
        // }
        // std::cout<< "\n\n";
        // std::cout << std::endl;
        //compute colors returns pixels
        // fill in buffer using counterline and i
        int offsetTile = t_currentline*160 + i*8;
        
       // //std::cout << (offset)<< " *";
       for(int l = 0; l<8 ;++l){
           RGBBuffer[offsetTile + l] = lineOfPixels.at(l);
       }
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



void Ppu::fillLineOfTileDB(WORD t_addr){    //type = 0 -> BG, type = 1 -> Sprite
        WORD lineOfATile;
        int currentLine =0;
        for(int r = 0 ; r< 8 ; ++r){
            lineOfATile = (memory->readByte(t_addr +2*r)<<8) + (memory->readByte(t_addr +2*r +1)); //16B = tile dimension
           
            std::vector<RGBColor> lineOfPixels = toPixels(lineOfATile);
            for(int k = 0 ; k< 8 ;++k){
                if(lineOfPixels.at(k).r == 255){
                    std::cout << "  ";
                }
                else
                {
                    std::cout << "1 ";
                }  
        }
        currentLine++;
        std::cout<< "\n";
        }
}






void Ppu::renderBGLine(BYTE t_currentline){
    // CI VUOLE ANCHE LA SCANLINEEEE
    BYTE scrollY = getScrollY() >> 3;
    BYTE scrollX = getScrollX() >> 3;  
    BYTE LCDcontrolRegister = getLCDControlRegister();    
    WORD BGMemoryStart = LCDcontrolRegister & 0x08 ? 0x9C00 : 0x9800;
    BGMemoryStart = 0x9800;
    BYTE tileID;
    WORD offset;
    for(int i = 0; i < SCREEN_WIDTH/8 ; ++i){
        if((LCDcontrolRegister & 0x10) && (t_currentline >= getWindowY()) && (i > (getWindowX() - 7)/8)){
           // return;
        }
        offset = ((scrollY/8 + (int)t_currentline/8)%32)*32 + ((scrollX/8 + i)%32);
        tileID = memory->readByte(BGMemoryStart + offset);
        //std::cout << "Tile ID: "<< std::hex<< (int)tileID << "\t" << "memory address: "<< std::hex<< (int)(BGMemoryStart + i )<< "\n";
        fillLineOfTile(tileID, i, t_currentline, 0); //0 = tileID;
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
        fillLineOfTile(tileID, i,7, 0);
    }

}

void Ppu::renderSpriteLine(){


}