#include "../includes/cpu.hpp"
//#include "../includes/memory.hpp"
#include "../includes/interrupts.hpp"
//#include "../includes/instruction.hpp"

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <unistd.h>
#include <bitset>

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



void Cpu::printCpuState(){
    std::cout<<"-------------------------------------------------\n";
    std::cout<< "PC: "<< std::hex<< (int)getPC() - 1 << std::endl;
    std::cout<< "SP: "<< std::hex<< (int)getSP() << std::endl << std::endl;
    std::cout<< "A: "<< std::hex<< (int)getA() << std::endl;
    std::cout<< "B: "<< std::hex<< (int)getB() << std::endl;
    std::cout<< "C: "<< std::hex<< (int)getC() << std::endl;
    std::cout<< "D: "<< std::hex<< (int)getD() << std::endl;
    std::cout<< "E: "<< std::hex<< (int)getE() << std::endl;
    std::cout<< "H: "<< std::hex<< (int)getH() << std::endl;
    std::cout<< "L: "<< std::hex<< (int)getL() << std::endl;
    std::cout<< "F: "<< std::bitset<8>(getF()) << std::endl;
    // std::cout<< "AF: "<< std::hex<< (int)getAF() << std::endl;
    // std::cout<< "BC: "<< std::hex<< (int)getBC() << std::endl;
    // std::cout<< "DE: "<< std::hex<< (int)getDE() << std::endl;
    // std::cout<< "HL: "<< std::hex<< (int)getHL() << std::endl;
}

BYTE Cpu::step() {
    BYTE opcode = Cpu::fetch();
    std::cout<<std::hex<<"OPCODE: " << (int)opcode<<std::endl;
    instruction instr = Cpu::decode(opcode);
    std::cout<<instr.name<<'\t'<<(int)instr.cycles<<'\t'<<instr.function<<std::endl;
    return Cpu::execute(instr);
}

void Cpu::stepDebug(std::set<BYTE>* old_opcode){
    BYTE opcode = Cpu::fetch();
    instruction instr = Cpu::decode(opcode);
    if(old_opcode->find(opcode) == old_opcode->end()){
        old_opcode->insert(opcode);
        printCpuState();
        std::cout<<instr.name<<'\t'<<(int)opcode<<std::endl;
    }
    Cpu::execute(instr);
   
    
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

    //std::cout<<"initInstructions called"<<std::endl;
    //fill the instructions map
    Cpu::initInstructions();
    //std::cout<<"initInstructions done"<<std::endl;
    //std::cout<<"---------------------------------------------> "<<instrSet.size()<<std::endl;
    //std::cout<<"---------------------------------------------> "<<instrSetCBPrefix.size()<<std::endl;

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
    //Cpu::step();        //for debug
}

BYTE Cpu::fetch(void) {
    //std::cout<<"fetch"<<std::endl;
    //unsigned char opcode = 0x80;//
    BYTE opcode = mem->readByte(pc);
    incPC();

    return opcode;
}

struct instruction Cpu::decode(BYTE opcode) {
   // std::cout<<"decode"<<std::endl;
    
    //return instrSet.at(0x80);
    return instrSet.at(opcode);
}

BYTE Cpu::execute(instruction instr) {
   // std::cout<<"execute"<<std::endl;
    instr.function(this);

    //return clock cycles to update the counter
    return instr.cycles;
}

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
