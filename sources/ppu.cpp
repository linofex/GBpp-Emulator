#include "../includes/ppu.hpp"
#include <iostream>
#include <algorithm>

Ppu::Ppu(Memory* t_memory): memory(t_memory), spritePixelPriority(160*144,false), RGBBuffer(160*144,{0,0,0}){
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
        renderSpriteLine(t_currentline);
        //std::cout<< "SPRITE";
    }
    int a = 0;
   // std::cout<< "############################# " << (int)(a+ bufferY) << std::endl;
    // /bufferY = (++bufferY)%140;
}

std::vector<RGBColor> Ppu::toPixels(WORD t_lineOfTile, BYTE t_palette, bool flipX){

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
    std::vector<RGBColor> pixelsInTileLine;

    for(int i = 0; i < 8; ++i) {
        // remeber 7-1, otherwise tiles flip
        k = (flipX == true) ? i : (7 - i);
        
        BYTE lsb = (data0 & (1 << k)) >> k;
        BYTE msb = (data1 & (1 << k)) >> k;
        //RGBColor rgb = getRGBColor(((msb << 1) + lsb) >> 2*i);
        RGBColor rgb = getRGBColor((msb << 1) + lsb, palette);
        pixelsInTileLine.push_back(rgb);
    }
    return pixelsInTileLine;
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
        offset = ((signed char) t_tileID + 128)*16;
    }
    //std::vector<WORD> tile = {0X0000, 0X3c3c, 0X6666 ,0X6666 ,0X6666 ,0X6666,0X3c3c, 0X0000};

    //for(int j = 0; j < 16 ; j+= 2){
        //one line of the tile
        //lineOfATile = tile.back();
        //tile.pop_back();
        lineOfATile = memory->readWord(startAddress + (t_currentline % 8)*2 + offset); //16B = tile dimension
        
        std::vector<RGBColor> lineOfPixels = toPixels(lineOfATile, 2, false);
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
        int offsetTile = t_currentline*160 + i*8;
        
        // //std::cout << (offset)<< " *";
        for(int l = 0; l < 8; ++l){
            RGBBuffer[offsetTile + l] = lineOfPixels.at(l);

            //bitmap for BG and sprites priority -> if BG is WHITE, sprite always on top (even if has no priority)
            spritePixelPriority[offsetTile + l] = (lineOfPixels.at(l).r == 255) ? true : false;
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
           
            std::vector<RGBColor> lineOfPixels = toPixels(lineOfATile, 2, false);
            /* for(int k = 0 ; k< 8 ;++k){
                if(lineOfPixels.at(k).r == 255){
                    std::cout << "  ";
                }
                else
                {
                    std::cout << "1 ";
                }  
            } */
        currentLine++;
        //std::cout<< "\n";
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
        //if(t_currentline % 8 == 0) {
            //std::cout <<std::hex<<(int) tileID<<" ";
            //getchar();//system("PAUSE");
        //}
        //std::cout << "Tile ID: "<< std::hex<< (int)tileID << "\t" << "memory address: "<< std::hex<< (int)(BGMemoryStart + i )<< "\n";
        fillLineOfTile(tileID, i, t_currentline, 0); //0 = tileID;
    }
    //if(t_currentline % 8 == 0)
        //std::cout<<std::endl;

    // increase scrollX e scrollY? quando? secondo me no va fatt noi

}

void Ppu::renderWindowLine(BYTE){
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

sprite Ppu::getSprite(BYTE spriteNum) {
    WORD spriteAddr = 0xFE00 + 4*spriteNum;
    sprite spriteInfo;
    spriteInfo.posY = memory->readByte(spriteAddr++);
    spriteInfo.posX = memory->readByte(spriteAddr++);
    spriteInfo.patternNum = memory->readByte(spriteAddr++);
    spriteInfo.attribs = memory->readByte(spriteAddr);
    //std::cout<<"PatNumb: "<<std::hex<<(int)spriteInfo.patternNum<<std::endl;
    /* if(spriteInfo.patternNum == 58) {    
        std::cout<<"PosY: "<<std::hex<<(int)spriteInfo.posY<<std::endl;
        std::cout<<"PosX: "<<std::hex<<(int)spriteInfo.posX<<std::endl;
        std::cout<<"PatNumb: "<<std::hex<<(int)spriteInfo.patternNum<<std::endl;
        std::cout<<"Attribs: "<<std::hex<<(int)spriteInfo.attribs<<std::endl;
        std::cout<<"__________________________________________"<<std::endl;
    } */

    return spriteInfo;    
}


/* std::vector<RGBColor> Ppu::flipY(std::vector<RGBColor> t_rgb) {
    std::vector<RGBColor> reverse;// = std::reverse(t_rgb.begin(),t_rgb.end()); 
    return reverse;
} */

std::vector<std::vector<RGBColor>> Ppu::buildSprite(sprite t_sprite) {  
    BYTE height = 8;
    std::vector<std::vector<RGBColor>> pixelOfASprite;
    WORD lineOfASprite;
    WORD spriteStartAddr = 0x8000 + 16*t_sprite.patternNum;
    BYTE paletteNum;
   
    if(getLCDControlRegister() & 0x04) {    //sprite size is 8x16
        height = 16;
    }
    bool flipOnX = isFlippedX(t_sprite.attribs);
    for(int i = 0; i < 8; ++i) {
        lineOfASprite = (memory->readByte(spriteStartAddr +2*i)<<8) + (memory->readByte(spriteStartAddr +2*i +1));
        //if(t_sprite.patternNum == 0x58)
           // std::cerr<<"\n___"<<pixelOfASprite.size()<<std::endl;
        
        //if(isFlippedX(t_sprite.attribs)) {
        pixelOfASprite.push_back(toPixels(lineOfASprite, Ppu::getPaletteNum(t_sprite.attribs), flipOnX));
        if(height == 16) {
            pixelOfASprite.push_back(toPixels(lineOfASprite, Ppu::getPaletteNum(t_sprite.attribs), flipOnX));
        }        
    }
 //    }

    if(isFlippedY(t_sprite.attribs)) {
        std::reverse(pixelOfASprite.begin(),pixelOfASprite.end()); 
    }

    //        std::cerr<<"\n________________________________"<<std::hex<<(int)lineOfASprite<<std::endl;
    //if(t_sprite.patternNum == 0x58) {
        //std::cerr<<"\n"<<std::hex<<(int)t_sprite.patternNum<<" "<<pixelOfASprite.size()<<std::endl;
    //}
    /* if(t_sprite.patternNum == 0x25) {
        for(int i = 0; i < 8 ;++i){
            for(int k = 0; k < 8 ;++k){
                if(pixelOfASprite.at(i).at(k).r == 255){
                    std::cout << " ";
                }
                else {
                    std::cout << "1 ";
                }
            
            }
            std::cout <<"\n";
        }
    } */

    
    return pixelOfASprite;
}

void Ppu::renderSpriteLine(BYTE t_currentline) {  
    std::vector<std::vector<RGBColor>> spritePixels;
    sprite spriteInfo;
    
    BYTE height = 8;
    //std::cout<<std::endl;   
    for(int i = 0; i < 40; ++i) {
        spriteInfo = Ppu::getSprite(i);
        spritePixels = Ppu::buildSprite(spriteInfo);
        //std::cout<<std::hex<<(int)spriteInfo.patternNum<<"\t";
        if(getLCDControlRegister() & 0x04) {    //sprite size is 8x16
            height = 16;
        }

        int startY = (int)(spriteInfo.posY) - 16;
        int startX = (int)(spriteInfo.posX) - 8;        
        //int offsetSprite = ((int)spriteInfo.posY - 16) + ((int)spriteInfo.posX - 8);  
           
        for(int j = 0; j < 8; ++j) {

            /* if(spriteInfo.patternNum == 0x25) {
                if(((int)spritePixels.at(i).at(j).r/255) == 0)
                    std::cout<<"1 ";
                else
                    std::cout<<"  ";
            } */

            //check if the current scanline is inside the sprite (Y bounds)
            if((t_currentline >= startY) && (t_currentline < startY + height)) {     
                //check if BG has priority on transparent pixels of the sprite
                if(   isSpriteOnTop(spriteInfo.attribs) || 
                    (!isSpriteOnTop(spriteInfo.attribs) && spritePixelPriority[t_currentline*160 + startX + j])) {
                    //check if the new sprite has a higher color priority wrt the previous sprite drawn
                    //if(spritePixels.at(t_currentline % 8).at(j).r < RGBBuffer[t_currentline*160 + startX + j].r) { 
                
                        RGBBuffer[t_currentline*160 + startX + j] = spritePixels.at(t_currentline % 8).at(j);
                
                    //}
                }            
            }
        }
    }
}