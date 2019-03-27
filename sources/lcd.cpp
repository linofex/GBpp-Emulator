#include "../includes/lcd.hpp"
#include "../includes/memory.hpp"

Lcd::Lcd() {}

Lcd::Lcd(Memory* mem_/* , Gpu* gpu_ */) {
    mem = mem_;
    //gpu = gpu_;
    remainingCycles = 456;
}

bool Lcd::isLCDEnabled() {
    return (mem->readByte(LCDSTATUS) >> 7);
}
BYTE Lcd::getLCDMode() {
    return (mem->readByte(LCDSTATUS) & 0x03);
}
BYTE Lcd::getLCDModeRegister() {
    return mem->readByte(LCDSTATUS);
}
void Lcd::setLCDMode(BYTE t_val) {
    unsigned char mode = Lcd::getLCDModeRegister() & 0xFC;   //11111100
    unsigned char newMode = mode | t_val;

    mem->writeByte(LCDSTATUS, newMode);
}
unsigned char Lcd::getScanline() {
    return (mem->readByte(LCDLY));
}
void Lcd::setScanline(BYTE t_val) {
    mem->writeByte(LCDLY, t_val);
}
void Lcd::lcdStep(int cycles) {
    
    Lcd::setLCDStatus();

    if(!Lcd::isLCDEnabled())
        return;
    else
        remainingCycles -= cycles;

    unsigned char currentLine = Lcd::getScanline();

    if(remainingCycles <= 0) {
        remainingCycles = 456;

        if(currentLine < 144) {         //visible scanlines [0, 143]
            //Gpu.drawLine()
            Lcd::setScanline(currentLine++);
        }
        else if(currentLine == 144) {   //VBLANK interrupt request
            mem->RequestInterrupt(VBLANK);
            Lcd::setScanline(currentLine++);
        }
        else if(currentLine == 154) {   //invisible scanlines [144, 153]
            Lcd::setScanline(0);        //go to the next line
        }
        else
            Lcd::setScanline(currentLine++);
    }
}
void Lcd::setLCDStatus() {

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
            mem->RequestInterrupt(LCD);
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

