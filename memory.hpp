#ifndef define MEMORY_H
#define MEMORY_H

namespace GBemulator{

#define KB 0x400 // 1024B
#define B  0x1    // 1B
  0000-3FFF   16KB ROM Bank 00     (in cartridge, fixed at bank 00)
  4000-7FFF   16KB ROM Bank 01..NN (in cartridge, switchable bank number)
  8000-9FFF   8KB Video RAM (VRAM) (switchable bank 0-1 in CGB Mode)
  A000-BFFF   8KB External RAM     (in cartridge, switchable bank, if any)
  C000-CFFF   4KB Work RAM Bank 0 (WRAM)
  D000-DFFF   4KB Work RAM Bank 1 (WRAM)  (switchable bank 1-7 in CGB Mode)
  E000-FDFF   Same as C000-DDFF (ECHO)    (typically not used)
  FE00-FE9F   Sprite Attribute Table (OAM)
  FEA0-FEFF   Not Usable
  FF00-FF7F   I/O Ports
  FF80-FFFE   High RAM (HRAM)
  FFFF        Interrupt Enable Register

    class Memory{
        private:
            unsigned char rom[32*KB]; // 0000-7FFF space where the rom is stored 
            unsigned char vRam[8*KB]; // 8000-9FFF space where video memory is stored
            unsigned char eRam[8*KB]; // A000-BFFF in cartridge space
            unsigned char wram[8*KB]; // C000-CFFF space of work ram 
            unsigned char echowRam[8*KB]; // echo space of the internal ram
            unsigned char OAM[160*B];  // FE00-FE9F space  where sprite attributes reside (Sprite Attribute Table)
            unsigned char ioPorts[127*B]; // FF00-FF7F I/O ports
            unsigned char hRam[128*B]; // high ram
            unsigned char IEReg; // Interrupt Enable Register

        public: 

    }

}

#endif

