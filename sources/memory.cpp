
#include "../includes/memory.hpp"
#include "../includes/dma.hpp"
#include "../includes/timer.hpp"
#include <iostream>
//#include "../includes/cpu.hpp"

/*
    According to PanDoc http://bgb.bircd.org/pandocs.htm#memorymap 
    unsigned char rom[32*KB];     // 0000-7FFF space where the rom is stored 
    unsigned char vRam[8*KB];     // 8000-9FFF space where video memory is stored
    unsigned char eRam[8*KB];     // A000-BFFF in cartridge space
    unsigned char wram[8*KB];     // C000-CFFF space of work ram 
    unsigned char echowRam[8*KB]; // E000-FDFF echo space of the internal ram
    unsigned char OAM[160*B];     // FE00-FE9F space where sprite attributes reside (Sprite Attribute Table)
                                  // FEA0-FEFF not Usable
    unsigned char ioPorts[127*B]; // FF00-FF7F I/O ports
    unsigned char hRam[127*B];    // FF80-FFFE high ram
    unsigned char IEReg;          // Interrupt Enable Register
*/

Memory::Memory():
    rom(32*KB,0x00),
    vRam(8*KB,0x00),
    eRam(8*KB,0x00),
    wRam(8*KB, 0x00),
    echowRam(8*KB,0x00),
    OAM(160,0x00),
    ioPorts(128, 0x00),
    hRam(127,0x00){
    
    bios = (std::vector<BYTE>{  0x31, 0xFE, 0xFF, 0xAF, 0x21, 0xFF, 0x9F, 0x32, 0xCB, 0x7C, 0x20, 0xFB, 0x21, 0x26, 0xFF, 0x0E, 
                                0x11, 0x3E, 0x80, 0x32, 0xE2, 0x0C, 0x3E, 0xF3, 0xE2, 0x32, 0x3E, 0x77, 0x77, 0x3E, 0xFC, 0xE0, 
                                0x47, 0x11, 0x04, 0x01, 0x21, 0x10, 0x80, 0x1A, 0xCD, 0x95, 0x00, 0xCD, 0x96, 0x00, 0x13, 0x7B, 
                                0xFE, 0x34, 0x20, 0xF3, 0x11, 0xD8, 0x00, 0x06, 0x08, 0x1A, 0x13, 0x22, 0x23, 0x05, 0x20, 0xF9, 
                                0x3E, 0x19, 0xEA, 0x10, 0x99, 0x21, 0x2F, 0x99, 0x0E, 0x0C, 0x3D, 0x28, 0x08, 0x32, 0x0D, 0x20, 
                                0xF9, 0x2E, 0x0F, 0x18, 0xF3, 0x67, 0x3E, 0x64, 0x57, 0xE0, 0x42, 0x3E, 0x91, 0xE0, 0x40, 0x04, 
                                0x1E, 0x02, 0x0E, 0x0C, 0xF0, 0x44, 0xFE, 0x90, 0x20, 0xFA, 0x0D, 0x20, 0xF7, 0x1D, 0x20, 0xF2, 
                                0x0E, 0x13, 0x24, 0x7C, 0x1E, 0x83, 0xFE, 0x62, 0x28, 0x06, 0x1E, 0xC1, 0xFE, 0x64, 0x20, 0x06, 
                                0x7B, 0xE2, 0x0C, 0x3E, 0x87, 0xE2, 0xF0, 0x42, 0x90, 0xE0, 0x42, 0x15, 0x20, 0xD2, 0x05, 0x20, 
                                0x4F, 0x16, 0x20, 0x18, 0xCB, 0x4F, 0x06, 0x04, 0xC5, 0xCB, 0x11, 0x17, 0xC1, 0xCB, 0x11, 0x17, 
                                0x05, 0x20, 0xF5, 0x22, 0x23, 0x22, 0x23, 0xC9, 0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 
                                0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D, 0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E, 
                                0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99, 0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC, 
                                0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E, 0x3C, 0x42, 0xB9, 0xA5, 0xB9, 0xA5, 0x42, 0x3C, 
                                0x21, 0x04, 0x01, 0x11, 0xA8, 0x00, 0x1A, 0x13, 0xBE, 0x20, 0xFE, 0x23, 0x7D, 0xFE, 0x34, 0x20, 
                                0xF5, 0x06, 0x19, 0x78, 0x86, 0x23, 0x05, 0x20, 0xFB, 0x86, 0x20, 0xFE, 0x3E, 0x01, 0xE0, 0x50
                            });

    keyStatus = 0xFF;
    ioPorts[0xFF00 & 0x07F] = 0xCF;
    readOnlyRom = false;
    bootPhase = false;
    timer = NULL;
    }

void Memory::setJoypadStatus(BYTE t_joypadStatus){keyStatus = t_joypadStatus;}

void Memory::loadROM(const std::vector<BYTE>* t_rom){
    std::copy(t_rom->begin(),t_rom->end(),rom.begin());
}

BYTE Memory::buildJoypadStatus(WORD t_add) {
    BYTE joypad = ioPorts.at(t_add & 0x007F);
    BYTE keys = 0x00;
    if((joypad & 0x30) == 32) {     //Select direction keys (select = 0)
        keys = (keyStatus & 0x0F);
    }
    else if((joypad & 0x30) == 16){                          //Select button keys (select = 0)
        keys = (keyStatus >> 4);
    }
    BYTE status = (joypad & 0xF0) | keys;
    return status;
}

BYTE Memory::readByte(const WORD t_add) {
            
   // ROM
    if(t_add < 0x8000){
        if(t_add < 0x00FF && bootPhase){ //boot phase
            return bios.at(t_add);
        }
        return rom.at(t_add);
    }
    // Video Memory
    else if (t_add>= 0x8000 && t_add < 0xA000){
        return vRam.at(t_add & 0x1FFF); // from 0 to 8191 (8KB)
    }
    // external memory
    else if (t_add >= 0xA000 && t_add < 0xC000){
        return eRam.at(t_add & 0x1FFF); // from 0 to 8191 (8KB)
    }
    // work memory
    else if (t_add >= 0xC000 && t_add < 0xE000){
        return wRam.at(t_add & 0x1FFF); // from 0 to 8191 (8KB)
    }
    // echo ram
    else if (t_add >= 0xE000 && t_add < 0xFE00){
        return eRam.at(t_add & 0x1FFF); // from 0 to 8191 (8KB)
    }
    // OAM
    else if (t_add >= 0xFE00 && t_add < 0xFEA0){
        return OAM.at(t_add & 0x00FF); // from 0 to 159
    }
    else if(t_add >= 0xFEA0 && t_add < 0xFEFF){
      //std::cout << "[ERROR] MEMORY location not usable!\n";
      return 0x00;
    }
    // I/O ports
    else if (t_add >= 0xFF00 && t_add < 0xFF80){
        if(t_add == 0xFF00) {    //JOYPAD status register
            return buildJoypadStatus(t_add);
        }
       
        return ioPorts.at(t_add & 0x007F); // from 0 to 127
        
    }
    // high speed ram
    else if(t_add >= 0xFF80 && t_add < 0xFFFF){
        return hRam.at(t_add & 0x007F); // from to 0 to 127
    }
    //Interrupt Enable Register
    else{ 
        return IEReg;  
    }
}

WORD Memory::readWord(const WORD t_add) {
    return readByte(t_add) + (readByte(t_add + 1) << 8);
}


void Memory::writeByte(const WORD t_add, BYTE t_value){
    // ROM
    if(t_add < 0x8000 && !readOnlyRom){
        rom[t_add] = t_value;
    }
    
    // Video Memory
    else if (t_add>= 0x8000 && t_add < 0xA000){
       // std::cout<<"SCRIVO I TILE " << std::hex << (int)t_value<<std::endl;
        vRam[t_add & 0x1FFF] = t_value; // from 0 to 8191 (8KB)
    }
    // external memory
    else if (t_add >= 0xA000 && t_add < 0xC000){
        eRam[t_add & 0x1FFF] = t_value; // from 0 to 8191 (8KB)
    }
    // work memory
    else if (t_add >= 0xC000 && t_add < 0xE000){
         //std::cout << "BG!: " << std::hex <<(int)t_value<< "\n";
        wRam[t_add & 0x1FFF] = t_value; // from 0 to 8191 (8KB)
        echowRam[t_add & 0x1FFF] = t_value; // from 0 to 8191 (8KB)
         
    }
    // echo ram
    else if (t_add >= 0xE000 && t_add < 0xFE00){
        echowRam[t_add & 0x1FFF] = t_value; // from 0 to 8191 (8KB)
        wRam[t_add & 0x1FFF] = t_value; // from 0 to 8191 (8KB)
         
    }

    // OAM
    else if (t_add >= 0xFE00 && t_add < 0xFEA0){
        OAM[t_add & 0x00FF] = t_value; // from 0 to 159 (8KB)
    }
    else if(t_add >= 0xFEA0 && t_add < 0xFEFF){
      //std::cout << "[ERROR] MEMORY location not writable!\n";
    }

    // I/O ports
    else if (t_add >= 0xFF00 && t_add < 0xFF80){
        if(t_add == TMC){
            BYTE currFrequency = readByte(TMC) & 0x03;
            ioPorts[t_add & 0x007F] = t_value;
            BYTE newFrequency = readByte(TMC) & 0x03;

            if(newFrequency != currFrequency) {
                timer->setTimer();
            }
            return;
        }
       
        ioPorts[t_add & 0x007F] = t_value; 
        if(t_add == 0xFF46){
           // std::cerr <<"\n\n**** DMA!! "<< std::endl;
            startDMATransfer(this); //start DMA transfer
            return;
        }
       
    }
    // high speed ram
    else if(t_add >= 0xFF80 && t_add < 0xFFFF){
        hRam[t_add & 0x007F] = t_value; // from to 0 to 125
    }
    //Interrupt Enable Register (necessario?)
    else if (t_add == 0xFFFF){  
        IEReg = t_value;
    }  
}

void Memory::writeWord(const WORD t_add, WORD t_value){
    writeByte(t_add, t_value & 0xFF); // First byte
    writeByte(t_add + 1, (t_value >> 8) & 0xFF);  // Second byte
}

/* void Memory::writeInStack(Cpu* t_cpu, WORD t_value){
    // WORD sp = t_cpu;
    writeWord(t_cpu->getSP(), t_value);
    t_cpu->decSP();
} */
void Memory::linkTimer(Timer* t_timer) {
    timer = t_timer;
}

Memory::~Memory(){
}