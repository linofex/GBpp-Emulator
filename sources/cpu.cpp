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
    mem = m; //RICORDATELO
    Cpu::reset();
    Cpu::initInstructions();
    clockCycles = 0;
    flag = false;
    lastOpcode = 0x00;
    opcode = 0x00;
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
    // std::cerr<< "A: "<< std::hex<< (int)getA() << "\t";
    // std::cerr<< "B: "<< std::hex<< (int)getB() << "\t";
    // std::cerr<< "C: "<< std::hex<< (int)getC() << "\t";
    // std::cerr<< "D: "<< std::hex<< (int)getD() << "\t";
    // std::cerr<< "E: "<< std::hex<< (int)getE() << "\t";
    // std::cerr<< "H: "<< std::hex<< (int)getH() << "\t";
    // std::cerr<< "L: "<< std::hex<< (int)getL() << "\t";
    // std::cerr<< "F: "<< std::bitset<8>(getF()) << "\n";
    
    // Print CPU registers states
    std::cout<< "\nAF: "<< std::hex<< (int)getAF() << std::endl;
    std::cout<< "BC: "<< std::hex<< (int)getBC() << std::endl;
    std::cout<< "DE: "<< std::hex<< (int)getDE() << std::endl;
    std::cout<< "HL: "<< std::hex<< (int)getHL() << std::endl;
    std::cout<< "SP: "<< std::hex<< (int)getSP() << "\t";
    std::cout<< "\nPC: "<< std::hex<< (int)getPC()<< "\t";
    std::cout<< "0xFF44: "<< std::hex<< (int)mem->readByte(0xFF44) << std::endl;
    
    std::cout<< "Opcode: "<< std::hex<< (int)opcode << std::endl;
    std::cout<< "Instruction: "<< instrSet.at(opcode).name << std::endl;
    //std::cout<< "Last Opcode: "<< std::hex<< (int)lastOpcode << std::endl;
    
    // Print registers
    std::cout << "IER: " << std::hex<< (int)mem->readByte(IER_ADD) << std::endl;
    std::cout << "IRR: " << std::hex<< (int)mem->readByte(IRR_ADD) << std::endl;
    std::cout << "LCDCONTROL: " << std::hex<< (int)mem->readByte(LCDCONTROL) << std::endl;
    std::cout << "LCDSTATUS: " << std::hex<< (int)mem->readByte(LCDSTATUS) << std::endl;
    std::cout << "SCANLINE: " << std::hex<< (int)mem->readByte(LCDLY) << std::endl;
    std::cout << "LCDLYC: " << std::hex<< (int)mem->readByte(LCDLYC) << std::endl;

    std::cout << "SCROLLX: " << std::hex<< (int)mem->readByte(SCROLLX) << std::endl;
    std::cout << "SCROLLY: " << std::hex<< (int)mem->readByte(SCROLLY) << std::endl;


    std::cout << "INTERRUPTS: " << ((isIntMasterEnable() == true) ? "ENABLED" : "DISAABLED") <<  std::endl;

    
     

    // std::cerr<< "0xFF44: "<< std::hex<< (int)getSP() << "\t";
    // std::cerr<< "\0xFF44: "<< std::hex<< (int)getPC()<< "\t";

     

}

BYTE Cpu::step() {
    if(isHalted() ||  isStopped()){
        //std::cout << "HALT";
        return 100;
    }
    //std::cerr<<"PC: "<<std::hex << (int)getPC()<< "\n";
    opcode = Cpu::fetch();
    instruction instr = Cpu::decode(opcode);
    // std::cout<< o <<std::endl;
    BYTE ret = Cpu::execute(instr);
   // std::cerr <<  "\tI: " <<instr.name<<"\toc: "<<std::hex<<(int)opcode<< std::endl;
    //printCpuState();
    if(isLastOpcode(0xFB) || isLastOpcode(0xD9)){  //EI and RETI sets interrupts one machine clock cycle after
        setIntMasterEnable();
    }
    setLastOpcode(opcode);
    return ret;
}

void Cpu::stepDebug(std::set<BYTE>* old_opcode){
    bool flag = false;
    std::cout<< "********************************************************************************************\n";
    printCpuState();
    opcode = Cpu::fetch();
    instruction instr = Cpu::decode(opcode);
    if(old_opcode->find(opcode) == old_opcode->end()){
        old_opcode->insert(opcode);
        flag = true;
        //std::cout<<instr.name<<'\t'<<(int)opcode<<std::endl;
    }
    Cpu::execute(instr);
    // if(old_opcode->find(opcode) == old_opcode->end()){
    //     old_opcode->insert(opcode);
    //     std::cout<<instr.name<<'\t'<<(int)opcode<<std::endl;
    //     if(old_opcode->find(opcode) == old_opcode->end()){
    //     old_opcode->insert(opcode);
    //     std::cout<<instr.name<<'\t'<<(int)opcode<<std::endl;
    // }
    printCpuState();
    std::cout<< (flag==true?"\nNEW":"\nDONE") << "\tInstruction: " <<instr.name<<"\topcode: "<<(int)opcode<< std::endl;
    std::cout<< "********************************************************************************************\n";


    
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

    //std::cout<<"initInstructions called"<<std::endl;
    //fill the instructions map
    //Cpu::initInstructions();
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
    halt = false;
    stop = false;
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
    return instrSet.at(opcode);
}

BYTE Cpu::execute(instruction instr) {
   // std::cout<<"execute"<<std::endl;
    instr.function(this);

    //return clock cycles to update the counter
    return instr.cycles;
}

void Cpu::pushWord(WORD t_val) { 
    decSP();
    decSP();
    mem->writeWord(getSP(), t_val);
//     std::cout << "SP_value: " << std::hex << (int)t_val<< "\n";
//     std::cout << "SP_add: " << std::hex << (int)sp<< "\n";
}

void Cpu::push(BYTE t_val) {
    //aggiungere controllo dell'indirizzo >>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    decSP();
    mem->writeByte(getSP(), t_val);
    
}

WORD Cpu::popWord() {
    BYTE temp = Cpu::popByte();
    return temp + (Cpu::popByte() << 8); // secondo me il <<8 deve andare a temp, ma non funiona lo stesso

}

BYTE Cpu::popByte() {
    BYTE temp = mem->readByte(getSP());
    incSP();
    return temp;
}
