#include "../includes/cpu.hpp"
//#include "../includes/memory.hpp"
#include "../includes/interrupts.hpp"
//#include "../includes/instruction.hpp"

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <unistd.h>

Cpu::Cpu(void) { } 

Cpu::Cpu(Memory* m) {
    mem = m; //RICORDATELO
    Cpu::reset();
    std::cout<<"reset end"<<std::endl;
}
Cpu::~Cpu(void) {
    std::cout << "CPU distruttore\n";
    //exit(1);
}

void Cpu::initInstructions() {
    init(instrSet);
    initCBPrefix(instrSetCBPrefix);
}

struct instruction Cpu::getInstrSetAt(BYTE t_opcode) {
    return instrSet.at(t_opcode);
}

struct instruction Cpu::getInstrSetCBPrefixAt(BYTE t_opcode) {
    return instrSetCBPrefix.at(t_opcode);
}

BYTE Cpu::step() {
    
    unsigned char opcode = 0x80;//mem->readByte(pc);
   
    //std::cout<<i.name<<'\t'<<i.cycles<<'\t'<<i.paramNum<<'\t'<<i.function<<std::endl;

    //BYTE opcode = Cpu::fetch();
    instruction instr = Cpu::decode(opcode);
    return Cpu::execute(instr);
    
}

void Cpu::reset() {

    //security check for original cartridge
    //if(!Cpu::checkCartridge())
        //halt
        //return;

    //initialization of special registers
    pc = 0x100;
    sp = 0xFFFE;

    //initialization of internal registers
    regAF.reg = 0x01B0;
    regBC.reg = 0x0013;
    regDE.reg = 0x00D8;
    regHL.reg = 0x014D;

    std::cout<<"initInstructions called"<<std::endl;
    //fill the instructions map
    Cpu::initInstructions();
    std::cout<<"initInstructions done"<<std::endl;

    //initialization of I/O registers in the internal RAM
    mem->writeByte(0xFF05, 0x00);	//mem->writeByte
    mem->writeByte(0xFF06, 0x00);
    mem->writeByte(0xFF07, 0x00);
    mem->writeByte(0xFF10, 0x80);
    mem->writeByte(0xFF11, 0xBF);
    mem->writeByte(0xFF12, 0xF3);
    mem->writeByte(0xFF14, 0xBF);
    mem->writeByte(0xFF16, 0x3F);
    mem->writeByte(0xFF17, 0x00);
    mem->writeByte(0xFF19, 0xBF);
    mem->writeByte(0xFF1A, 0x7F);
    mem->writeByte(0xFF1B, 0xFF);
    mem->writeByte(0xFF1C, 0x9F);
    mem->writeByte(0xFF1E, 0xBF);
    mem->writeByte(0xFF20, 0xFF);
    mem->writeByte(0xFF21, 0x00);
    mem->writeByte(0xFF22, 0x00);
    mem->writeByte(0xFF23, 0xBF);
    mem->writeByte(0xFF24, 0x77);
    mem->writeByte(0xFF25, 0xF3);
    mem->writeByte(0xFF26, 0xF1);
    mem->writeByte(0xFF40, 0x91);
    mem->writeByte(0xFF42, 0x00);
    mem->writeByte(0xFF43, 0x00);
    mem->writeByte(0xFF45, 0x00);
    mem->writeByte(0xFF47, 0xFC);
    mem->writeByte(0xFF48, 0xFF);
    mem->writeByte(0xFF49, 0xFF);
    mem->writeByte(0xFF4A, 0x00);
    mem->writeByte(0xFF4B, 0x00);
    mem->writeByte(0xFFFF, 0x00);
    
    intMasterEnable = false;
}

BYTE Cpu::fetch(void) {
    std::cout<<"fetch"<<std::endl;
    unsigned char opcode = 0x80;//mem->readByte(pc);
    incPC();

    return opcode;
}

struct instruction Cpu::decode(BYTE opcode) {
    std::cout<<"decode"<<std::endl;
    std::cout<<"---------------------------------------------> "<<instrSet.size()<<std::endl;
    
    return instrSet.at(0x80);
}

BYTE Cpu::execute(instruction instr) {
    std::cout<<"execute"<<std::endl;
    instr.function(this);

    //update the clock cycles counter
    return instr.cycles;
    //check for interrupts >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
}

// void Cpu::updateTimers(int cycles) {
//     Cpu::stepTimer(cycles);
//     Cpu::stepDivider(cycles);
// }

// bool Cpu::isTimerOn() {
//     BYTE tmc = mem->readByte(TMC);
//     return ((tmc >> 2) & 1);
// }

// void Cpu::setTimer() {
    
//     if(!isTimerOn())
//         return;

//     int oldTimer = mem->readByte(TMC);   //timer controller register
//     int newTimer = 0;

//     //00: 4096Hz    01: 262144Hz    10: 65536Hz     11: 16384Hz
//     switch(oldTimer & 0x03) {
//         case 0:
//             newTimer = 1024; // 1024 = CLOCK/4096Hz
//             break;
//         case 1:
//             newTimer = 16;   //   16 = CLOCK/262144Hz
//             break;
//         case 2:
//             newTimer = 64;   //   64 = CLOCK/65536Hz
//             break;
//         case 3:
//             newTimer = 256;  //  256 = CLOCK/16384Hz
//             break;
//         default:
//             exit(1);
//             std::cout<<"Invalid timer"<<std::endl;
//             break; 
//     }

//     timerCounter = newTimer;
// }

// void Cpu::stepDivider(int cycles) {
    
//     //divider always done
//     dividerCounter += cycles;
    
//     if(dividerCounter >= 0xFF) {   //next is an overflow (255)
//         dividerCounter = 0x00;
//         mem->writeByte(DIVIDER, dividerCounter);
//     }
// }

// void Cpu::stepTimer(int cycles) {
    
//     if(!isTimerOn())
//         return;

//     timerCounter -= cycles;
//     if(timerCounter <= 0) {
//         //timer is reset again to the value specified by the timer controller TMC
//         Cpu::setTimer();
//         BYTE tima = mem->readByte(TIMA);

//         if(tima == 0xFF) {              //next is an overflow (255)
//             BYTE tma = mem->readByte(TMA);
//             mem->writeByte(TIMA, tma);

//             //send timer interrupt ______________________________>>>>>>>>>>>>>>>>>>>>>>>>

//         } else {            //increment the counter
//             mem->writeByte(TIMA, tima + 1);
//         }
//     }
// }


void Cpu::pushWord(WORD t_val) {
    mem->writeWord(getSP(), t_val);
    incSP();
    incSP();
}

void Cpu::push(BYTE t_val) {
    //aggiungere controllo dell'indirizzo >>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    mem->writeWord(getSP(), t_val);
    incSP();
}

WORD Cpu::popWord() {
    BYTE temp = Cpu::popByte();
    return temp + (Cpu::popByte() << 8);
}

BYTE Cpu::popByte() {
    BYTE temp = mem->readWord(getSP());
    decSP();
    return temp;
}
