#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "utility.hpp"

class Cpu;
class Memory;

//namespace GBemulator{
    class InterruptHnadler{
        private:
            bool intMasterEnable; // An interrupt can only be served IFF this is TRUE
        public:
            InterruptHnadler():intMasterEnable(true){}
            void RequestInterrupt(const BYTE t_interrupt, Memory& t_memory);
            void ServeInterrupt(const BYTE t_interrupt, Memory& t_memory, Cpu* t_cpu);
            void DoInterrupt(Memory& t_memory, Cpu* t_cpu);
    };
//}


#endif