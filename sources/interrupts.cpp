#include "../includes/interrupts.hpp"
#include "../includes/memory.hpp"
#include "../includes/cpu.hpp"


void InterruptHnadler::ServeInterrupt(const BYTE t_interrupt, Memory& t_memory, Cpu* t_cpu){
    intMasterEnable = false;                    // RETI and EI instructions enable it again
    BYTE irr = t_memory.readByte(IRR_ADD);          // Read Interrupt Request Reister from memory at 0x0FF0F
    t_memory.writeByte(IRR_ADD, irr ^ t_interrupt); // Reset the Interrupet flag to 0, since is served

    // Save PC in the stack
    t_memory.writeInStack(t_cpu, t_cpu->getPC());
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
    }
}

void InterruptHnadler::DoInterrupt(Memory& t_memory, Cpu* t_cpu){
    if (intMasterEnable){
        BYTE ier = t_memory.readByte(IER_ADD); //Read Interrupt Enable Reister from memory at 0x0FF0F
        BYTE irr = t_memory.readByte(IRR_ADD); //Read Interrupt Request Reister from memory at 0x0FF0F
        
        /* If the interrupt is enabled AND the interrupt is requested --> ServeInterrupt */
        /*          IN ORDER OF PRIORITY            */
        if(ier & VBLANK & irr)  return ServeInterrupt(VBLANK, t_memory, t_cpu); // Higher priority
        if(ier & LCD & irr)     return ServeInterrupt(LCD, t_memory, t_cpu);
        if(ier & TIMER & irr)   return ServeInterrupt(TIMER, t_memory, t_cpu);
        if(ier & JOYPAD & irr)  return ServeInterrupt(JOYPAD, t_memory, t_cpu);   
    }
}