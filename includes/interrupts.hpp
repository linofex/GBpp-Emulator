#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "utility.hpp"

class Cpu;
class Memory;

class InterruptHandler{
    private:
    public:
        static void serveInterrupt(const BYTE, Memory*, Cpu*);
        static bool doInterrupt(Memory*, Cpu*);
        static void requestInterrupt(Memory*, const BYTE);
};

#endif