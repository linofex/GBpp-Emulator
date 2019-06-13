#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "utility.hpp"

class Cpu;
class Memory;

//namespace GBemulator{
    class InterruptHandler{
        private:
        public:
            //InterruptHnadler(){}
            static void serveInterrupt(const BYTE, Memory*, Cpu*);
            static bool doInterrupt(Memory*, Cpu*);
            static void requestInterrupt(Memory*, const BYTE);
    };
//}


#endif