#include "../includes/interrupts.hpp"
#include "../includes/memory.hpp"
#include "../includes/cpu.hpp"
#include <iostream>


void InterruptHandler::serveInterrupt(const BYTE t_interrupt, Memory* t_memory, Cpu* t_cpu){
    t_cpu->resetIntMasterEnable();                      // RETI and EI instructions enable it again
    t_cpu->resethalt();                                 // exit halt CPU
    t_cpu->pushWord(t_cpu->getPC());                    // Save PC in the stack

    BYTE irr = t_memory->readByte(IRR_ADD);             // Read Interrupt Request Register from memory at 0xFF0F
    t_memory->writeByte(IRR_ADD, irr ^ t_interrupt);    // Reset the Interrupet flag to 0, since is served
    
    // Point the PC to the interrupt routine
    switch (t_interrupt){
        case VBLANK:
            t_cpu->setPC(VBLANK_ADD);
            break;
        case LCD:
            t_cpu->setPC(LCD_ADD);
            break;
        case TIMER:
            t_cpu->setPC(TIMER_ADD);
            break;
        case JOYPAD:
            t_cpu->setPC(JOYPAD_ADD);
            t_cpu->resetStop();
    }
    t_cpu->addClockCycles(12);
}

bool InterruptHandler::doInterrupt(Memory* t_memory, Cpu* t_cpu){
    BYTE ier = t_memory->readByte(IER_ADD); //Read Interrupt Enable Register from memory at 0xFFFF
    BYTE irr = t_memory->readByte(IRR_ADD); //Read Interrupt Request Register from memory at 0xFF0F
    if (t_cpu->isIntMasterEnable()){
        /* If the interrupt master is enabled AND the interrupt is requested --> ServeInterrupt
           IN ORDER OF PRIORITY            */
        if(ier & VBLANK & irr)  { serveInterrupt(VBLANK, t_memory, t_cpu); return true;} // Higher priority
        if(ier & LCD & irr)     { serveInterrupt(LCD, t_memory, t_cpu); return false;}
        if(ier & TIMER & irr)   { serveInterrupt(TIMER, t_memory, t_cpu); return false;}
        if(ier & JOYPAD & irr)  { serveInterrupt(JOYPAD, t_memory, t_cpu); return false;}   
    }
    else{
        if (t_cpu->isHalted() && ((ier & irr) > 0)) {
                t_cpu->resethalt();
            }
            return false;
    }
    return false;
}

void InterruptHandler::requestInterrupt(Memory* t_mem, const BYTE t_interrupt){
    BYTE irr = t_mem->readByte(IRR_ADD);          // Read Interrupt Request Register from memory at 0x0FF0F
    t_mem->writeByte(IRR_ADD, irr | t_interrupt); // Set the Interrupt flag to 1, since requested    
}