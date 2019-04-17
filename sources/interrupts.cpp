#include "../includes/interrupts.hpp"
#include "../includes/memory.hpp"
#include "../includes/cpu.hpp"
#include <iostream>


void InterruptHandler::serveInterrupt(const BYTE t_interrupt, Memory* t_memory, Cpu* t_cpu){
    t_cpu->resetIntMasterEnable();                    // RETI and EI instructions enable it again
    t_cpu->resethalt(); // power on the CPU
    t_cpu->pushWord(t_cpu->getPC());  // Save PC in the stack

    BYTE irr = t_memory->readByte(IRR_ADD);          // Read Interrupt Request Reister from memory at 0x0FF0F
    //std::cout << "Lo tolgo:";
    t_memory->writeByte(IRR_ADD, irr ^ t_interrupt); // Reset the Interrupet flag to 0, since is served
    
     
    //t_memory.writeInStack(t_cpu, t_cpu->getPC());

    // Point the PC to the interrupt routine
    switch (t_interrupt){
        case VBLANK:
            //std::cout << "V_BLANK" << std::endl;
            t_cpu->setPC(VBLANK_ADD);
            //std::cout << std::hex << (int)t_cpu->getPC() << std::endl;
            break;
        case LCD:
            t_cpu->setPC(LCD_ADD);
            break;
        case TIMER:
            t_cpu->setPC(TIMER_ADD);
            break;
        case JOYPAD:
            //std::cout << "JOYPAD\n" << std::endl;
            t_cpu->setPC(JOYPAD_ADD);
            t_cpu->resetStop();
    }
}

void InterruptHandler::doInterrupt(Memory* t_memory, Cpu* t_cpu){
//        std::cerr << "DIS";
    BYTE ier = t_memory->readByte(IER_ADD); //Read Interrupt Enable Reister from memory at 0x0FFFF
    BYTE irr = t_memory->readByte(IRR_ADD); //Read Interrupt Request Reister from memory at 0x0FF0F
        
    if (t_cpu->isIntMasterEnable()){
        // if(t_cpu->getInstrSetAt(t_cpu->getPC()).name == "HALT"){
        //     t_cpu->incPC();
        // }
        //std::cout << "\n**enabled\n";
        //std::cerr<< std::hex << (int)ier << std::endl;
        //std::cout << std::hex << (int)irr << std::endl;
        /* If the interrupt is enabled AND the interrupt is requested --> ServeInterrupt */
        /*          IN ORDER OF PRIORITY            */
        if(ier & VBLANK & irr)  {/* std::cout << "INT\n"; */return serveInterrupt(VBLANK, t_memory, t_cpu);} // Higher priority
        if(ier & LCD & irr)     {/* std::cout << "INT\n"; */return serveInterrupt(LCD, t_memory, t_cpu);}
        if(ier & TIMER & irr)   {/*std::cout << "INT\n";*/return serveInterrupt(TIMER, t_memory, t_cpu);}
        if(ier & JOYPAD & irr)  {std::cerr << "JOYPAD\n";return serveInterrupt(JOYPAD, t_memory, t_cpu);}   
    }
    else{
        //std::cout << "\ndisabled\n";
        if (t_cpu->isHalted() && ((ier & irr) > 0)) {
                t_cpu->resethalt();
            }
            return;
    }
}

void InterruptHandler::requestInterrupt(Memory* t_mem, const BYTE t_interrupt){
    BYTE irr = t_mem->readByte(IRR_ADD);          // Read Interrupt Request Reister from memory at 0x0FF0F
    //std::cout << "REQQ"<<std::hex << (int)(irr | t_interrupt) << std::endl;
    t_mem->writeByte(IRR_ADD, irr | t_interrupt); // Set the Interrupt flag to 1, since requested
    
}