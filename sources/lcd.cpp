#include "../includes/lcd.hpp"
#include "../includes/ppu.hpp"
#include "../includes/memory.hpp"
#include"../includes/interrupts.hpp"
#include <iostream>
Lcd::Lcd() {
    
}

Lcd::Lcd(Memory* t_memory, Ppu* t_ppu) : memory(t_memory), ppu(t_ppu){
    remainingCycles = 456;
    setLCDMode(MODE2);
}

bool Lcd::isLCDEnabled() {
    return (memory->readByte(LCDCONTROL) >> 7);
}

BYTE Lcd::getLCDMode() {
    return (memory->readByte(LCDSTATUS) & 0x03);
}

BYTE Lcd::getLCDModeRegister() {
    return memory->readByte(LCDSTATUS);
}

void Lcd::setLCDMode(BYTE t_val) {
    unsigned char mode = Lcd::getLCDModeRegister() & 0xFC;   //11111100
    unsigned char newMode = mode | t_val;

    memory->writeByte(LCDSTATUS, newMode);
}

unsigned char Lcd::getScanline() {
    return (memory->readByte(LCDLY));
}

void Lcd::setScanline(BYTE t_val) {
    memory->writeByte(LCDLY, t_val);
}

// void Lcd::step(int cycles) {
//     Lcd::setLCDStatus();

//     if(!Lcd::isLCDEnabled()){
//         return;
//     }
//     else
//         remainingCycles -= cycles;
    
//     // std::cout <<"RC: "<<(int)remainingCycles<< std::endl;
//     // std::cout <<"CCC: "<<cycles<< std::endl;
    

//     unsigned char currentLine = Lcd::getScanline();

//     if(remainingCycles <= 0) {
//         remainingCycles = 456;

//         if(currentLine < 144) {         //visible scanlines [0, 143]
//             ppu->renderLine(currentLine);
//             Lcd::setScanline(++currentLine);
//         }
//         else if(currentLine == 144) {   //VBLANK interrupt request
//             InterruptHandler::requestInterrupt(memory, VBLANK);
//             Lcd::setScanline(++currentLine);
//         }
//         else if(currentLine == 154) {   //invisible scanlines [144, 153]
//             Lcd::setScanline(0);        //go to the next line
//         }
//         else
//             Lcd::setScanline(++currentLine);
//     }
// }

// void Lcd::setLCDStatus() {
//     if(!isLCDEnabled()){
//         Lcd::setLCDMode(MODE1);
//         Lcd::setScanline(0);
//         remainingCycles = 456;
//         return;
//     }

//     unsigned char oldMode = Lcd::getLCDMode();

//     if(Lcd::getScanline() >= 144 && Lcd::getScanline() <= 153)
//         Lcd::setLCDMode(MODE1);
//     else{
//         if(remainingCycles < 204)
//             Lcd::setLCDMode(MODE0);
//         else if(remainingCycles < 376)
//             Lcd::setLCDMode(MODE3);
//         else if(remainingCycles < 456)
//             Lcd::setLCDMode(MODE2);
//     }
    
    
//     unsigned char newMode = Lcd::getLCDMode();

//     if((oldMode != newMode) && (newMode != MODE3))
//         if(Lcd::testInterrupt(newMode))
//             InterruptHandler::requestInterrupt(memory, LCD);
//     if(testCoincidence()){
//         InterruptHandler::requestInterrupt(memory, LCD);
//     }
// }


void Lcd::step(int cycles){
    if(memory->readByte(LCDLY) == memory->readByte(LCDLYC)){
        BYTE lcdstatus = memory->readByte(LCDSTATUS);
        lcdstatus |= 0X04; //set bit 2 to 1
        memory->writeByte(LCDSTATUS, lcdstatus);
    }
    remainingCycles -= cycles;
    unsigned char currentLine = Lcd::getScanline();
    switch (getLCDMode()) {
        case MODE2: //OAM
            if (remainingCycles < 376){
                Lcd::setLCDMode(MODE3);
            }
            break;
        case MODE3: //LCD Driver
            if(remainingCycles < 204){
                Lcd::setLCDMode(MODE0);
                if(isLCDEnabled()){
                    ppu->renderLine(currentLine);
                }
                if(Lcd::testInterrupt(MODE0))
                    InterruptHandler::requestInterrupt(memory, LCD);

            }
            break;
        case MODE0: //HBLANK
            if(remainingCycles < 0){
                setScanline(++currentLine);
                if(currentLine == 143){
                    Lcd::setLCDMode(MODE1);
                    InterruptHandler::requestInterrupt(memory, VBLANK);
                    if(Lcd::testInterrupt(MODE1))
                        InterruptHandler::requestInterrupt(memory, LCD);
                    
                }
                else{
                    setLCDMode(MODE2);
                    if(Lcd::testInterrupt(MODE2))
                        InterruptHandler::requestInterrupt(memory, LCD);
                    if(Lcd::testCoincidence())
                        InterruptHandler::requestInterrupt(memory, LCD);   
                }
                remainingCycles = 456;
            }
            break;
        case MODE1: //VBLANK
            if (remainingCycles < 0){
                setScanline(++currentLine);
                if(currentLine == 153){
                    setLCDMode(MODE2);
                    setScanline(0);
                }
                //else{
                    remainingCycles = 456;
                //}
            }
            break;
    }
}


bool Lcd::testInterrupt(BYTE t_mode) {
    switch(t_mode) {
        case MODE0:
            if(t_mode & 0x08)       //MODE0 interrupt enabled
                return true;
        case MODE1:
            if(t_mode & 0x10)       //MODE1 interrupt enabled
                return true;
        case MODE2:
            if(t_mode & 0x20)       //MODE2 interrupt enabled
                return true;
        default:
            return false;
    }

    return false;
}


bool Lcd::testCoincidence(){
    BYTE lcdstatus = memory->readByte(LCDSTATUS);
    if(memory->readByte(LCDLY) == memory->readByte(LCDLYC) && lcdstatus & 0x40){
        return true;
    }
    return false;
}
//         lcdstatus |= 0X04; //set bit 2 to 1
//         coincidenceFlag = true;
//     }

//}
// bool Lcd::testCoincidence(){
//     BYTE lcdstatus = memory->readByte(LCDSTATUS);
//     bool coincidenceFlag = false;
//     if(memory->readByte(LCDLY) == memory->readByte(LCDLYC)){
//         lcdstatus |= 0X04; //set bit 2 to 1
//         coincidenceFlag = true;
//     }
//     // else{
//     //     lcdstatus &= 0XFB; //set bit 2 to 0
//     // }
//     memory->writeByte(LCDSTATUS, lcdstatus);
//     if(coincidenceFlag && (lcdstatus & 0x40)){ // check coincidence enable bit 6
//         return true;    //request interrupt
//     }
//     return false; // do nothing
// }

void Lcd::renderScreen(SDL_Renderer* t_renderer, SDL_Texture* t_texture) {
    SDL_UpdateTexture(t_texture, NULL, ppu->getRGBBuffer(), SCREEN_WIDTH * sizeof (uint32_t));
    SDL_RenderClear(t_renderer);
    SDL_RenderCopy(t_renderer, t_texture, NULL, NULL);
    SDL_RenderPresent(t_renderer);

    
    // for (int i = 0; i < SCREEN_HEIGHT ; ++i){
    //     for(int j= 0; j< SCREEN_WIDTH;++j){
    //        std::cerr<<buffer->at(i*SCREEN_WIDTH + j)<<"\t";
    //        //color =  buffer->at(i*SCREEN_WIDTH + j);
    //        //SDL_SetRenderDrawColor(t_renderer, (Uint8)color.r, (Uint8)color.g, (Uint8)color.b, 255);
    //        //SDL_RenderDrawPoint(t_renderer, j, i);
    //     }
    //     std::cerr<<""<<std::endl;
  //  }    
    
    /*const std::vector<RGBColor>* buffer = ppu->getRGBBuffer();
    RGBColor color;
    for (int i = 0; i < SCREEN_HEIGHT ; ++i){
        for(int j= 0; j< SCREEN_WIDTH;++j){
           color =  buffer->at(i*SCREEN_WIDTH + j);
          //  std::cout<<"\n R:" << (int)color.r <<" G:" << (int)color.g <<" B:" << (int)color.b <<std::endl;

          //SDL_SetRenderDrawColor(t_renderer, rand()/255, rand()/255, rand()/255,255);
           SDL_SetRenderDrawColor(t_renderer, (Uint8)color.r, (Uint8)color.g, (Uint8)color.b, 255);
           SDL_RenderDrawPoint(t_renderer, j, i);
        }
       //SDL_RenderPresent(t_renderer);
    }
    SDL_RenderPresent(t_renderer);*/
    //getchar();
}