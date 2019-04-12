
#include "../includes/memory.hpp"
#include "../includes/dma.hpp"
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
        keyStatus = 0x00;
    }

void Memory::setJoypadStatus(BYTE t_joypadStatus){keyStatus = t_joypadStatus;}
BYTE Memory::buildJoypadStatus(WORD t_add) const {
    BYTE joypad = ioPorts.at(t_add & 0x007F);
    BYTE keys = 0x00;

    if((joypad & 0x30) == 32) {     //Select direction keys (select = 0)
        keys = (keyStatus & 0x0F);
    }
    else {                          //Select button keys (select = 0)
        keys = (keyStatus >> 4);
    }
    return (joypad & 0xF0) | keys;
}

BYTE Memory::readByte(const WORD t_add) {
    // ROM
    if(t_add < 0x8000){
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
      std::cout << "[ERROR] MEMORY location not usable!\n";
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


void Memory::writeByte(const WORD t_add, const BYTE t_value){
    // ROM
    if(t_add < 0x8000){
        rom[t_add] = t_value;
    }
    // Video Memory
    else if (t_add>= 0x8000 && t_add < 0xA000){
        std::cout<<"SCRIVO I TILE " << std::hex << (int)t_value<<std::endl;
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
    }
    // echo ram
    else if (t_add >= 0xE000 && t_add < 0xFE00){
         eRam[t_add & 0x1FFF] = t_value; // from 0 to 8191 (8KB)
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
        if(t_add == LCDCONTROL){
            std::cerr << " WRITE IN BGP: "<<std::hex<<(int)t_value << std::endl;
          //  return;
        }
        // if(t_add == 0xFF44)
        //     std::cerr <<"CI SCRIV0 "<< std::hex << (int)t_value;
        ioPorts[t_add & 0x007F] = t_value; 
        

        if(t_add == 0xFF46){
            std::cerr <<"\n\n**** DMA!! "<< std::endl;
            startDMATransfer(this); //start DMA transfer
            return;
        }
    }
    // high speed ram
    else if(t_add >= 0xFF80 && t_add < 0xFFFF){
         hRam[t_add & 0x007F] = t_value; // from to 0 to 125
    }
    //Interrupt Enable Register (necessario?)
    else {  
        IEReg = t_add;
    }  
}

void Memory::writeWord(const WORD t_add, const WORD t_value){
    writeByte(t_add, t_value & 0xFF); // First byte
    writeByte(t_add + 1, (t_value >> 8) & 0xFF);  // Second byte
}

/* void Memory::writeInStack(Cpu* t_cpu, WORD t_value){
    // WORD sp = t_cpu;
    writeWord(t_cpu->getSP(), t_value);
    t_cpu->decSP();
} */

Memory::~Memory(){
    std::cout << "MEMORY distruttore\n";
}