#include "../includes/interrupts.hpp"
#include "../includes/memory.hpp"
#include "../includes/cpu.hpp"
#include <iostream>


void InterruptHandler::serveInterrupt(const BYTE t_interrupt, Memory* t_memory, Cpu* t_cpu){
    t_cpu->resetIntMasterEnable();                    // RETI and EI instructions enable it again
    BYTE irr = t_memory->readByte(IRR_ADD);          // Read Interrupt Request Reister from memory at 0x0FF0F
    t_memory->writeByte(IRR_ADD, irr ^ t_interrupt); // Reset the Interrupet flag to 0, since is served

    // Save PC in the stack
    t_cpu->pushWord(t_cpu->getPC());
    
    t_cpu->resethalt(); // power on the CPU
    //t_memory.writeInStack(t_cpu, t_cpu->getPC());
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
}

void InterruptHandler::doInterrupt(Memory* t_memory, Cpu* t_cpu){
//        std::cerr << "DIS";

    if (t_cpu->isIntMasterEnable()){
        std::cerr << "INT";
        if(t_cpu->getInstrSetAt(t_cpu->getPC()).name == "HALT")
            t_cpu->incPC();

        BYTE ier = t_memory->readByte(IER_ADD); //Read Interrupt Enable Reister from memory at 0x0FF0F
        BYTE irr = t_memory->readByte(IRR_ADD); //Read Interrupt Request Reister from memory at 0x0FF0F
        
        /* If the interrupt is enabled AND the interrupt is requested --> ServeInterrupt */
        /*          IN ORDER OF PRIORITY            */
        if(ier & VBLANK & irr)  return serveInterrupt(VBLANK, t_memory, t_cpu); // Higher priority
        if(ier & LCD & irr)     return serveInterrupt(LCD, t_memory, t_cpu);
        if(ier & TIMER & irr)   return serveInterrupt(TIMER, t_memory, t_cpu);
        if(ier & JOYPAD & irr)  return serveInterrupt(JOYPAD, t_memory, t_cpu);   
    }
}

void InterruptHandler::requestInterrupt(Memory* t_mem, const BYTE t_interrupt){
    BYTE irr = t_mem->readByte(IRR_ADD);          // Read Interrupt Request Reister from memory at 0x0FF0F
    t_mem->writeByte(IRR_ADD, irr | t_interrupt); // Set the Interrupt flag to 1, since requested
}