#ifndef MEMORY_H
#define MEMORY_H
#include"utility.hpp"
//#include"cpu.hpp"
#include <vector>


class Cpu;

//namespace GBemulator{
    class Memory{
        private:

            std::vector<BYTE>rom;     // 0000-7FFF space where the rom is stored 
            std::vector<BYTE>vRam;     // 8000-9FFF space where video memory is stored
            std::vector<BYTE>eRam;     // A000-BFFF in cartridge space
            std::vector<BYTE>wRam;     // C000-CFFF space of work ram 
            std::vector<BYTE>echowRam; // E000-FDFF echo space of the internal ram
            std::vector<BYTE>OAM;     // FE00-FE9F space  where sprite attributes reside (Sprite Attribute Table)
            std::vector<BYTE>ioPorts; // FF00-FF7F I/O ports
            std::vector<BYTE>hRam;    // high ram
            BYTE IEReg;          // Interrupt Enable Register

        public:
            Memory();
            // this method reads one byte ad address t_add
            BYTE readByte(const WORD t_add) const;
            // this method reads 2 byte starting from t_add
            WORD readWord(const WORD t_add) const; 

            // this method writes one byte ad address t_add
            void writeByte(const WORD t_add, const BYTE t_value);
            
            // this method writes 2 byte starting from t_add
            void writeWord(const WORD t_add, const WORD t_value);

            void writeInStack(Cpu* t_cpu, WORD t_value);

            void RequestInterrupt(const BYTE t_interrupt);
            ~Memory();
    };

//};
#endif

