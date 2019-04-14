#include "../includes/lcd.hpp"
#include "../includes/ppu.hpp"
#include "../includes/memory.hpp"
#include"../includes/interrupts.hpp"
#include <iostream>
Lcd::Lcd() {}

Lcd::Lcd(Memory* t_memory, Ppu* t_ppu) : memory(t_memory), ppu(t_ppu){
    remainingCycles = 456;
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

void Lcd::step(int cycles) {
    Lcd::setLCDStatus();

    if(!Lcd::isLCDEnabled()){
    //std::cerr << "D";
        return;
    }
    else
        remainingCycles -= cycles;
    
    // std::cout <<"RC: "<<(int)remainingCycles<< std::endl;
    // std::cout <<"CCC: "<<cycles<< std::endl;
    

    unsigned char currentLine = Lcd::getScanline();
   // std::cout << "*** CR ABILITATO **: "<<(int)currentLine << std::endl;


    if(remainingCycles <= 0) {
        remainingCycles = 456;

        if(currentLine < 144) {         //visible scanlines [0, 143]
            ppu->renderLine(currentLine);
            Lcd::setScanline(++currentLine);
        }
        else if(currentLine == 144) {   //VBLANK interrupt request
            std::cout<<"Interrupt VBLANK"<<std::endl;
            InterruptHandler::requestInterrupt(memory, VBLANK);
            Lcd::setScanline(++currentLine);
        }
        else if(currentLine == 154) {   //invisible scanlines [144, 153]
            Lcd::setScanline(0);        //go to the next line
        }
        else
            Lcd::setScanline(++currentLine);
    }
}

void Lcd::setLCDStatus() {
    if(!isLCDEnabled()){
<<<<<<< HEAD
        //std::cerr << "\nDISAB*************************************\n";
=======
>>>>>>> 2e757e937efa8c9e5add6dbd3c2bc22240b02f41
        Lcd::setLCDMode(MODE1);
        Lcd::setScanline(0);
        remainingCycles = 456;
        return;
    }

    unsigned char oldMode = Lcd::getLCDMode();

    if(remainingCycles < 204)
        Lcd::setLCDMode(MODE0);
    else if(remainingCycles < 376)
        Lcd::setLCDMode(MODE3);
    else if(remainingCycles < 456)
        Lcd::setLCDMode(MODE2);
    
    if(Lcd::getScanline() >= 144 && Lcd::getScanline() <= 153)
        Lcd::setLCDMode(MODE1);
    
    unsigned char newMode = Lcd::getLCDMode();

    if((oldMode != newMode) && (newMode != MODE3))
        if(Lcd::testInterrupt(newMode))
            InterruptHandler::requestInterrupt(memory, LCD);
    if(testCoincidence()){
        InterruptHandler::requestInterrupt(memory, LCD);
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
    bool coincidenceFlag = false;
    if(memory->readByte(LCDLY) == memory->readByte(LCDLYC)){
        lcdstatus |= 0X04; //set bit 2 to 1
        coincidenceFlag = true;
    }
    else{
        lcdstatus &= 0XFB; //set bit 2 to 0
    }
    memory->writeByte(LCDSTATUS, lcdstatus);
    if(coincidenceFlag && (lcdstatus & 0x40)){ // check coincidence enable bit 6
        return true;    //request interrupt
    }
    return false; // do nothing
}

void Lcd::renderScreen(SDL_Window* t_window, SDL_Renderer* t_renderer) {
    std::vector<RGBColor> buffer = ppu->getRGBBuffer();
    RGBColor color;
    for (int i = 0; i < SCREEN_HEIGHT ; ++i){
        for(int j= 0; j< SCREEN_WIDTH;++j){
           color =  buffer[i*SCREEN_WIDTH + j];
          //  std::cout<<"\n R:" << (int)color.r <<" G:" << (int)color.g <<" B:" << (int)color.b <<std::endl;

          //SDL_SetRenderDrawColor(t_renderer, rand()/255, rand()/255, rand()/255,255);
           SDL_SetRenderDrawColor(t_renderer, (Uint8)color.r, (Uint8)color.g, (Uint8)color.b, 255);
           SDL_RenderDrawPoint(t_renderer, j, i);
        }
         //SDL_RenderPresent(t_renderer);
    }
    SDL_RenderPresent(t_renderer);
    //getchar();
}