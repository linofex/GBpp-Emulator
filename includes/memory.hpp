#ifndef MEMORY_H
#define MEMORY_H
#include "utility.hpp"
#include <vector>

//   From Pandocs: http://bgb.bircd.org/pandocs.htm#lcdcontrolregister
//   0000-3FFF   16KB ROM Bank 00     (in cartridge, fixed at bank 00)
//   4000-7FFF   16KB ROM Bank 01..NN (in cartridge, switchable bank number)
//   8000-9FFF   8KB Video RAM (VRAM) (switchable bank 0-1 in CGB Mode)
//   A000-BFFF   8KB External RAM     (in cartridge, switchable bank, if any)
//   C000-CFFF   4KB Work RAM Bank 0 (WRAM)
//   D000-DFFF   4KB Work RAM Bank 1 (WRAM)  (switchable bank 1-7 in CGB Mode)
//   E000-FDFF   Same as C000-DDFF (ECHO)    (typically not used)
//   FE00-FE9F   Sprite Attribute Table (OAM)
//   FEA0-FEFF   Not Usable
//   FF00-FF7F   I/O Ports
//   FF80-FFFE   High RAM (HRAM)
//   FFFF        Interrupt Enable Register

class Cpu;
class Timer;

//namespace GBemulator{
    class Memory{
        private:
            std::vector<BYTE>rom;      // 0000-7FFF space where the rom is stored 
            std::vector<BYTE>vRam;     // 8000-9FFF space where video memory is stored
            std::vector<BYTE>eRam;     // A000-BFFF in cartridge space
            std::vector<BYTE>wRam;     // C000-CFFF space of work ram 
            std::vector<BYTE>echowRam; // E000-FDFF echo space of the internal ram
            std::vector<BYTE>OAM;      // FE00-FE9F space  where sprite attributes reside (Sprite Attribute Table)
            std::vector<BYTE>ioPorts;  // FF00-FF7F I/O ports
            std::vector<BYTE>hRam;     // high ram
            std::vector<BYTE>bios; 

            BYTE IEReg;                // Interrupt Enable Register

            BYTE keyStatus;
            bool readOnlyRom;
            bool bootPhase;
            
            Timer* timer;

        public:
            Memory();
            // this method reads one byte ad address t_add
            BYTE readByte(const WORD t_add);
            // this method reads 2 byte starting from t_add
            WORD readWord(const WORD t_add); 

            BYTE getJoypadStatus(void) const {return keyStatus;}
            BYTE buildJoypadStatus(WORD);
            void setJoypadStatus(BYTE);

            void loadROM(const std::vector<BYTE>*);
            // this method writes one byte ad address t_add
            void writeByte(const WORD t_add, BYTE t_value);
            void setReadOnlyRom(){ readOnlyRom = true;}
            void resetReadOnlyRom(){ readOnlyRom = false;}
            
            bool isBooting(){return bootPhase;}
            void resetBootPhase(){ bootPhase = false;}
            void setBootPhase(){ bootPhase = true;}


            // this method writes 2 byte starting from t_add
            void writeWord(const WORD t_add, WORD t_value);

            void writeInStack(Cpu* t_cpu, WORD t_value);
            void linkTimer(Timer*);

            ~Memory();
    };

//};
#endif

