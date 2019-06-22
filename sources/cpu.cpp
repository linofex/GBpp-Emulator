#include "../includes/cpu.hpp"
//#include "../includes/memory.hpp"
#include "../includes/interrupts.hpp"
//#include "../includes/instruction.hpp"

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <unistd.h>
#include <iostream>
#include <bitset>

Cpu::Cpu(void) { } 

Cpu::Cpu(Memory* m) {
    memory = m;
    Cpu::initInstructions();
    clockCycles = 0;
    lastOpcode = 0x00;
    opcode = 0x00;
    pc = 0x00;
    halt = false;
    stop = false;

}

Cpu::~Cpu(void) {
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


void Cpu::printCpuState(){
    // std::cerr<< "A: "<< std::hex<< (int)getA() << "\t";
    // std::cerr<< "B: "<< std::hex<< (int)getB() << "\t";
    // std::cerr<< "C: "<< std::hex<< (int)getC() << "\t";
    // std::cerr<< "D: "<< std::hex<< (int)getD() << "\t";
    // std::cerr<< "E: "<< std::hex<< (int)getE() << "\t";
    // std::cerr<< "H: "<< std::hex<< (int)getH() << "\t";
    // std::cerr<< "L: "<< std::hex<< (int)getL() << "\t";
    // std::cerr<< "F: "<< std::bitset<8>(getF()) << "\n";
    
    // Print CPU registers states
    // std::cout<< "\nAF: "<< std::hex<< (int)getAF() << std::endl;
    // std::cout<< "BC: "<< std::hex<< (int)getBC() << std::endl;
    // std::cout<< "DE: "<< std::hex<< (int)getDE() << std::endl;
    // std::cout<< "HL: "<< std::hex<< (int)getHL() << std::endl;
    // std::cout<< "SP: "<< std::hex<< (int)getSP() << "\t";
    // std::cout<< "\nPC: "<< std::hex<< (int)getPC()<< "\t";
    // std::cout<< "0xFF44: "<< std::hex<< (int)memory->readByte(0xFF44) << std::endl;
    
    // std::cout<< "Opcode: "<< std::hex<< (int)opcode << std::endl;
    // std::cout<< "Instruction: "<< instrSet.at(opcode).name << std::endl;
    //std::cout<< "Last Opcode: "<< std::hex<< (int)lastOpcode << std::endl;
    
    // Print registers
    // std::cout << "IER: " << std::hex<< (int)memory->readByte(IER_ADD) << std::endl;
    // std::cout << "IRR: " << std::hex<< (int)memory->readByte(IRR_ADD) << std::endl;
     std::cout << "LCDCONTROL: " << std::hex<< (int)memory->readByte(LCDCONTROL) << std::endl;
    //std::cout << "LCDSTATUS: " << std::hex<< (int)memory->readByte(LCDSTATUS) << std::endl;
    // std::cout << "SCANLINE: " << std::hex<< (int)memory->readByte(LCDLY) << std::endl;
    // std::cout << "LCDLYC: " << std::hex<< (int)memory->readByte(LCDLYC) << std::endl;

    //std::cout << "SCROLLX: " << std::hex<< (int)memory->readByte(SCROLLX) << std::endl;
    std::cout << "SCROLLY: " << std::hex<< (int)memory->readByte(SCROLLY) << std::endl;


    std::cout << "INTERRUPTS: " << ((isIntMasterEnable() == true) ? "ENABLED" : "DISAABLED") <<  std::endl;

    
     

    // std::cerr<< "0xFF44: "<< std::hex<< (int)getSP() << "\t";
    // std::cerr<< "\0xFF44: "<< std::hex<< (int)getPC()<< "\t";

     
    std::cout << "_____________________________________\n";
}

BYTE Cpu::step() {
    
    // if cpu is halted or stopped, return cycles and do nothing
    if(isHalted()){
        return getInstrSetAt(0x76).cycles;
    }
    else if(isStopped()){
        return getInstrSetAt(0x10).cycles;
    }

    // boot phase ended, reset the CPU and registers
    if(pc == 0xFE && memory->isBooting()){
        memory->resetBootPhase();
        reset();
    }
    opcode = Cpu::fetch();
    instruction instr = Cpu::decode(opcode);
    BYTE cycles = Cpu::execute(instr);
    if(isLastOpcode(0xFB) || isLastOpcode(0xD9)){  //EI and RETI sets interrupts one machine clock cycle after
        setIntMasterEnable();
    }
    setLastOpcode(opcode);
    return cycles;
}

void Cpu::reset() {

    //initialization of special registers
    pc = 0x100;
    sp = 0xFFFE;

    //initialization of internal registers
    regAF.reg = 0x01B0;
    regBC.reg = 0x0013;
    regDE.reg = 0x00D8;
    regHL.reg = 0x014D;

    //initialization of I/O registers in the internal RAM
    memory->writeByte(0xFF05, 0x00);	//memory->writeByte
    memory->writeByte(0xFF06, 0x00);
    memory->writeByte(0xFF07, 0x00);
    memory->writeByte(0xFF10, 0x80);
    memory->writeByte(0xFF11, 0xBF);
    memory->writeByte(0xFF12, 0xF3);
    memory->writeByte(0xFF14, 0xBF);
    memory->writeByte(0xFF16, 0x3F);
    memory->writeByte(0xFF17, 0x00);
    memory->writeByte(0xFF19, 0xBF);
    memory->writeByte(0xFF1A, 0x7F);
    memory->writeByte(0xFF1B, 0xFF);
    memory->writeByte(0xFF1C, 0x9F);
    memory->writeByte(0xFF1E, 0xBF);
    memory->writeByte(0xFF20, 0xFF);
    memory->writeByte(0xFF21, 0x00);
    memory->writeByte(0xFF22, 0x00);
    memory->writeByte(0xFF23, 0xBF);
    memory->writeByte(0xFF24, 0x77);
    memory->writeByte(0xFF25, 0xF3);
    memory->writeByte(0xFF26, 0xF1);
    memory->writeByte(0xFF40, 0x91);
    memory->writeByte(0xFF42, 0x00);
    memory->writeByte(0xFF43, 0x00);
    memory->writeByte(0xFF45, 0x00);
    memory->writeByte(0xFF47, 0xFC);
    memory->writeByte(0xFF48, 0xFF);
    memory->writeByte(0xFF49, 0xFF);
    memory->writeByte(0xFF4A, 0x00);
    memory->writeByte(0xFF4B, 0x00);
    memory->writeByte(0xFFFF, 0x00);
    
    intMasterEnable = false;
    halt = false;
    stop = false;
}

BYTE Cpu::fetch(void) {
    BYTE opcode = memory->readByte(pc);
    incPC();
    return opcode;
}

struct instruction Cpu::decode(BYTE opcode) {
    return instrSet.at(opcode);
}

BYTE Cpu::execute(instruction instr) {
    instr.function(this);
    //return clock cycles to update the counter
    return instr.cycles;
}

void Cpu::pushWord(WORD t_val) { 
    decSP();
    decSP();
    memory->writeWord(getSP(), t_val);

}

void Cpu::push(BYTE t_val) {
    decSP();
    memory->writeByte(getSP(), t_val);
    
}

WORD Cpu::popWord() {
    BYTE temp = Cpu::popByte();
    return temp + (Cpu::popByte() << 8); // secondo me il <<8 deve andare a temp, ma non funiona lo stesso

}

BYTE Cpu::popByte() {
    BYTE temp = memory->readByte(getSP());
    incSP();
    return temp;
}
