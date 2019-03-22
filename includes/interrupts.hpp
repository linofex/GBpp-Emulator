#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "utility.hpp"
#include "memory.hpp"

namespace GBemulator{
    class InterruptHnadler{
        private:
            bool intMasterEnable; // An interrupt can only be served IFF this is TRUE
        public:
            InterruptHnadler():intMasterEnable(true){}
            void RequestInterrupt(const BYTE t_interrupt, GBemulator::Memory& t_memory);
            void ServeInterrupt(const BYTE t_interrupt, GBemulator::Memory& t_memory, WORD* t_pc);
            void DoInterrupt(GBemulator::Memory& t_memory, WORD* t_pc);
    };
}


#endif