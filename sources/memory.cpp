
#include "../includes/memory.hpp"
#include <iostream>
//#include "../includes/cpu.hpp"

/*
    unsigned char rom[32*KB];     // 0000-7FFF space where the rom is stored 
    unsigned char vRam[8*KB];     // 8000-9FFF space where video memory is stored
    unsigned char eRam[8*KB];     // A000-BFFF in cartridge space
    unsigned char wram[8*KB];     // C000-CFFF space of work ram 
    unsigned char echowRam[8*KB]; // E000-FDFF echo space of the internal ram
    unsigned char OAM[160*B];     // FE00-FE9F space  where sprite attributes reside (Sprite Attribute Table)
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
    ioPorts(127, 0x00),
    hRam(127,0x00){}

BYTE Memory::readByte(const WORD t_add) const {
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
    else if (t_add >= 0xFE00 && t_add < 0xFF00){
        return OAM.at(t_add & 0x00FF); // from 0 to 159 (8KB)
    }
    // I/O ports
    else if (t_add >= 0xFF00 && t_add < 0xFF80){
        return ioPorts.at(t_add & 0x007F); //
    }
    // high speed ram
    else if(t_add >= 0xFF80 && t_add < 0xFFFF){
        return hRam.at(t_add & 0x007F); // from to 0 to 125
    }
    //Interrupt Enable Register
    else{ 
        return IEReg;  
    }
}

WORD Memory::readWord(const WORD t_add) const {
    return readByte(t_add) + (readByte(t_add + 1) << 8);
}


void Memory::writeByte(const WORD t_add, const BYTE t_value){
    // ROM
    if(t_add < 0x8000){
        rom[t_add] = t_value;
    }
    // Video Memory
    else if (t_add>= 0x8000 && t_add < 0xA000){
         vRam[t_add & 0x1FFF] = t_value; // from 0 to 8191 (8KB)
    }
    // external memory
    else if (t_add >= 0xA000 && t_add < 0xC000){
         eRam[t_add & 0x1FFF] = t_value; // from 0 to 8191 (8KB)
    }
    // work memory
    else if (t_add >= 0xC000 && t_add < 0xE000){
         wRam[t_add & 0x1FFF] = t_value; // from 0 to 8191 (8KB)
    }
    // echo ram
    else if (t_add >= 0xE000 && t_add < 0xFE00){
         eRam[t_add & 0x1FFF] = t_value; // from 0 to 8191 (8KB)
    }
    // OAM
    else if (t_add >= 0xFE00 && t_add < 0xFF00){
         OAM[t_add & 0x00FF] = t_value; // from 0 to 159 (8KB)
    }
    // I/O ports
    else if (t_add >= 0xFF00 && t_add < 0xFF80){
         ioPorts[t_add & 0x007F] = t_value; //
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