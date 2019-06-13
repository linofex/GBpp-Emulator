#include"../includes/timer.hpp"
#include"../includes/utility.hpp"
#include"../includes/memory.hpp"
#include"../includes/interrupts.hpp"


Timer::Timer(Memory* t_mem): memory(t_mem){
    timerCounter = 1024;
    dividerCounter = 0;
}
void Timer::updateTimers(unsigned long t_cycles) {
    Timer::stepTimer(t_cycles);
    Timer::stepDivider(t_cycles);
}

bool Timer::isTimerOn() {
    BYTE tmc = memory->readByte(TMC);
    return ((tmc >> 2) & 1);
}

void Timer::setTimer() {
    
    if(!isTimerOn())
        return;

    int oldTimer = memory->readByte(TMC);   //timer controller register
    int newTimer = 0;

    //00: 4096Hz    01: 262144Hz    10: 65536Hz     11: 16384Hz
    switch(oldTimer & 0x03) {
        case 0:
            newTimer = 1024; // 1024 = CLOCK/4096Hz
            break;
        case 1:
            newTimer = 16;   //   16 = CLOCK/262144Hz
            break;
        case 2:
            newTimer = 64;   //   64 = CLOCK/65536Hz
            break;
        case 3:
            newTimer = 256;  //  256 = CLOCK/16384Hz
            break;
        default:
            //exit(1);
            //std::cout<<"Invalid timer"<<std::endl;
            break; 
    }

    timerCounter = newTimer;
}

void Timer::stepDivider(unsigned long t_cycles) {
    
    //divider always done
    dividerCounter += t_cycles;
    
    if(dividerCounter >= 0xFF) {   //next is an overflow (255)
        dividerCounter = 0x00;
        memory->writeByte(DIVIDER, memory->readByte(DIVIDER) + 1); // the emulator cannot do this..
    }
}


void Timer::stepTimer(unsigned long t_cycles) {
    if(!isTimerOn())
        return;
    timerCounter -= t_cycles;
    if(timerCounter <= 0) {
        //timer is reset again to the value specified by the timer controller TMC
        Timer::setTimer();
        BYTE tima = memory->readByte(TIMA);

        if(tima == 0xFF) {              //next is an overflow (255)
            BYTE tma = memory->readByte(TMA);
            memory->writeByte(TIMA, tma);
            InterruptHandler::requestInterrupt(memory, TIMER); //send timer interrupt
            std::cout << "\ninterrupt\n";

        } else {            //increment the counter
            memory->writeByte(TIMA, tima + 1);
        }
    }
}
