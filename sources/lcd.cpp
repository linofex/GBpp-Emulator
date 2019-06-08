#include "../includes/lcd.hpp"
#include "../includes/ppu.hpp"
#include "../includes/memory.hpp"
#include"../includes/interrupts.hpp"
#include <iostream>
Lcd::Lcd() {}

Lcd::Lcd(Memory* t_memory, Ppu* t_ppu) : memory(t_memory), ppu(t_ppu){
    MODE_cycles = 0;
    setLCDMode(MODE0); // initially LCD controller is MODE0 = HBLANK
    setScanline(0);
}

bool Lcd::isLCDEnabled() {
    return (memory->readByte(LCDCONTROL) >> 7); // control bit 7 of FF40
}

BYTE Lcd::getLCDMode() {
    return (memory->readByte(LCDSTATUS) & 0x03); // get first 2bits of FF41
}

BYTE Lcd::getLCDModeRegister() {
    return memory->readByte(LCDSTATUS);
}

void Lcd::setLCDMode(BYTE t_val) {
    unsigned char mode = Lcd::getLCDModeRegister() & 0xFC;   //11111100
    memory->writeByte(LCDSTATUS, mode | t_val); // set the first 2 bits of FF41
}

unsigned char Lcd::getScanline() {
    return (memory->readByte(LCDLY));
}

void Lcd::setScanline(BYTE t_val) {
    memory->writeByte(LCDLY, t_val);
}

/*  from pandocs: http://bgb.bircd.org/pandocs.htm
    The Mode Flag goes through the values 0, 2, and 3 at a cycle of about 109uS.
    0 is present about 48.6uS, 2 about 19uS, and 3 about 41uS. This is interrupted 
    every 16.6ms by the VBlank (1). The mode flag stays set at 1 for about 1.08 ms.
    
    Mode 0 is present between 201-207 clks, 2 about 77-83 clks, and 3 about 169-175 clks. 
    A complete cycle through these states takes 456 clks. VBlank lasts 4560 clks. 
    A complete screen refresh occurs every 70224 clks.)
*/
 
void Lcd::step(int cycles){
    if(getScanline() == memory->readByte(LCDLYC)){
        BYTE lcdstatus = getLCDModeRegister();
        lcdstatus |= 0x04; //set bit 2 to 1
        memory->writeByte(LCDSTATUS, lcdstatus);
    }

    MODE_cycles += cycles;
        
    unsigned char currentLine = Lcd::getScanline();

    switch (getLCDMode()) {
        case MODE2: //OAM
            if (MODE_cycles >= 80){
                Lcd::setLCDMode(MODE3);
                MODE_cycles -= 80;
            }
            break;
        case MODE3: //LCD Driver
            if(MODE_cycles >= 172){
                Lcd::setLCDMode(MODE0);
                if(isLCDEnabled()){
                    ppu->renderLine(currentLine);
                }
                if(Lcd::testInterrupt(MODE0))
                    InterruptHandler::requestInterrupt(memory, LCD);

                MODE_cycles -= 172;
            }
            break;
        case MODE0: //HBLANK
            if(MODE_cycles >= 204){
                setScanline(++currentLine);
                if(currentLine == 144){
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
                MODE_cycles -= 204;
            }
            break;
        case MODE1: //VBLANK
            if (MODE_cycles  >= 456 ){
                setScanline(++currentLine);
                if(currentLine > 153){
                    setLCDMode(MODE2);
                    setScanline(0);

                }

                MODE_cycles -= 456;

            }
            break;
    }
}

// this method checks bits 3 to 6 for LCD interrupt from MODE
bool Lcd::testInterrupt(BYTE t_mode) {
    BYTE lcdstatus = memory->readByte(LCDSTATUS);
    switch(t_mode) {
        case MODE0:
            if(lcdstatus & 0x08)       //MODE0 interrupt enabled
                return true;
        case MODE1:
            if(lcdstatus & 0x10)       //MODE1 interrupt enabled
                return true;
        case MODE2:
            if(lcdstatus & 0x20)       //MODE2 interrupt enabled
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

// this method updates the screen
void Lcd::renderScreen(SDL_Renderer* t_renderer, SDL_Texture* t_texture) {
    SDL_UpdateTexture(t_texture, NULL, ppu->getRGBBuffer(), SCREEN_WIDTH * sizeof (uint32_t));
    SDL_RenderClear(t_renderer);
    SDL_RenderCopy(t_renderer, t_texture, NULL, NULL);
    SDL_RenderPresent(t_renderer);
}