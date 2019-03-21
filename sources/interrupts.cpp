#include "../includes/interrupts.hpp"
#include "../includes/memory.hpp"

void GBemulator::InterruptHnadler::RequestInterrupt(const BYTE t_interrupt, GBemulator::Memory& t_memory){
    BYTE irr = t_memory.readByte(IRR);          // Read Interrupt Request Reister from memory at 0x0FF0F
    t_memory.writeByte(IRR, irr | t_interrupt); // Set the Interrupt flag to 1, since requested
}


WORD GBemulator::InterruptHnadler::ServeInterrupt(const BYTE t_interrupt, GBemulator::Memory& t_memory){
    intMasterEnable = false;                    // RETI and EI instructions enable it again
    BYTE irr = t_memory.readByte(IRR);          // Read Interrupt Request Reister from memory at 0x0FF0F
    t_memory.writeByte(IRR, irr ^ t_interrupt); // Reset the Interrupet flag to 0, since is served

    // Point the PC to the interrupt routine
    switch (t_interrupt){
        case VBLANK:
            return VBLANK_ADD;
            break;
        case LCD:
            return VBLANK_ADD;
            break;
        case TIMER:
            return TIMER_ADD;
            break;
        case JOYPAD:
            return JOYPAD_ADD;
    }
}

WORD GBemulator::InterruptHnadler::DoInterrupt(GBemulator::Memory& t_memory){
    if (intMasterEnable){
        BYTE ier = t_memory.readByte(IER); //Read Interrupt Enable Reister from memory at 0x0FF0F
        BYTE irr = t_memory.readByte(IRR); //Read Interrupt Request Reister from memory at 0x0FF0F
        
        /* If the interrupt is enabled AND the interrupt is requested --> ServeInterrupt */
        /*          IN ORDER OF PRIORITY            */
        if(ier & VBLANK & irr) return ServeInterrupt(VBLANK, t_memory); // Higher priority
        if(ier & LCD & irr) return ServeInterrupt(LCD, t_memory);
        if(ier & TIMER & irr) return ServeInterrupt(TIMER, t_memory);
        if(ier & JOYPAD & irr) return ServeInterrupt(JOYPAD, t_memory);   
    }
}