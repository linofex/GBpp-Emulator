#include "../includes/interrupts.hpp"
#include "../includes/memory.hpp"

void GBemulator::InterruptHnadler::RequestInterrupt(const BYTE t_interrupt, GBemulator::Memory& t_memory){
    BYTE irr = t_memory.readByte(IRR_ADD);          // Read Interrupt Request Reister from memory at 0x0FF0F
    t_memory.writeByte(IRR_ADD, irr | t_interrupt); // Set the Interrupt flag to 1, since requested
}


void GBemulator::InterruptHnadler::ServeInterrupt(const BYTE t_interrupt, GBemulator::Memory& t_memory, WORD* t_pc){
    intMasterEnable = false;                    // RETI and EI instructions enable it again
    BYTE irr = t_memory.readByte(IRR_ADD);          // Read Interrupt Request Reister from memory at 0x0FF0F
    t_memory.writeByte(IRR_ADD, irr ^ t_interrupt); // Reset the Interrupet flag to 0, since is served

    // Point the PC to the interrupt routine
    switch (t_interrupt){
        case VBLANK:
            *t_pc = VBLANK_ADD;
            break;
        case LCD:
            *t_pc = VBLANK_ADD;
            break;
        case TIMER:
            *t_pc = TIMER_ADD;
            break;
        case JOYPAD:
            *t_pc = JOYPAD_ADD;
    }
}

void GBemulator::InterruptHnadler::DoInterrupt(GBemulator::Memory& t_memory, WORD* t_pc){
    if (intMasterEnable){
        BYTE ier = t_memory.readByte(IER_ADD); //Read Interrupt Enable Reister from memory at 0x0FF0F
        BYTE irr = t_memory.readByte(IRR_ADD); //Read Interrupt Request Reister from memory at 0x0FF0F
        
        /* If the interrupt is enabled AND the interrupt is requested --> ServeInterrupt */
        /*          IN ORDER OF PRIORITY            */
        if(ier & VBLANK & irr) return ServeInterrupt(VBLANK, t_memory, t_pc); // Higher priority
        if(ier & LCD & irr) return ServeInterrupt(LCD, t_memory,t_pc);
        if(ier & TIMER & irr) return ServeInterrupt(TIMER, t_memory, t_pc);
        if(ier & JOYPAD & irr) return ServeInterrupt(JOYPAD, t_memory,t_pc);   
    }
}