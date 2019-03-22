#include "../includes/cpu.hpp"
#include "../includes/memory.hpp"
#include "../includes/interrupts.hpp"

#include <iostream>
#include <map>
#include <string>
#include <fstream>

/* GBemulator::Cpu::Cpu(void) {
    reset();
} */

GBemulator::Cpu::Cpu(const GBemulator::Memory& m) {
    mem = m;
    reset();
}
GBemulator::Cpu::~Cpu(void) {
    exit(1);
}

instruction GBemulator::Cpu::addInstruction(std::string name, int cycles, int paramNum, void* function) {
    instruction i = {name, cycles, paramNum, function};
    return i;
}

void GBemulator::Cpu::fillInstructions() {

    //---------------------ADD------------------------------
    instrMap[0x80] = GBemulator::Cpu::addInstruction("ADD A, B", 4, 0, (void*)&GBemulator::Cpu::add_A_B);
    /* instrMap[0x81] = GBemulator::Cpu::addInstruction("ADD A, C", 4, 0, (void*)&GBemulator::Cpu::add_A_C);
    instrMap[0x82] = GBemulator::Cpu::addInstruction("ADD A, D", 4, 0, (void*)&GBemulator::Cpu::add_A_D);
    instrMap[0x83] = GBemulator::Cpu::addInstruction("ADD A, E", 4, 0, (void*)&GBemulator::Cpu::add_A_E);
    instrMap[0x84] = GBemulator::Cpu::addInstruction("ADD A, H", 4, 0, (void*)&GBemulator::Cpu::add_A_H);
    instrMap[0x85] = GBemulator::Cpu::addInstruction("ADD A, L", 4, 0, (void*)&GBemulator::Cpu::add_A_L);
    instrMap[0x86] = GBemulator::Cpu::addInstruction("ADD A, (HL)", 8, 0, (void*)&GBemulator::Cpu::add_A_HL_ind);
    instrMap[0x87] = GBemulator::Cpu::addInstruction("ADD A, A", 4, 0, (void*)&GBemulator::Cpu::add_A_A);
    //---------------------ADC------------------------------
    instrMap[0x88] = GBemulator::Cpu::addInstruction("ADC A, B", 4, 0, (void*)&GBemulator::Cpu::adc_A_B);
    instrMap[0x89] = GBemulator::Cpu::addInstruction("ADC A, C", 4, 0, (void*)&GBemulator::Cpu::adc_A_C);
    instrMap[0x8a] = GBemulator::Cpu::addInstruction("ADC A, D", 4, 0, (void*)&GBemulator::Cpu::adc_A_D);
    instrMap[0x8b] = GBemulator::Cpu::addInstruction("ADC A, E", 4, 0, (void*)&GBemulator::Cpu::adc_A_E);
    instrMap[0x8c] = GBemulator::Cpu::addInstruction("ADC A, H", 4, 0, (void*)&GBemulator::Cpu::adc_A_H);
    instrMap[0x8d] = GBemulator::Cpu::addInstruction("ADC A, L", 4, 0, (void*)&GBemulator::Cpu::adc_A_L);
    instrMap[0x8e] = GBemulator::Cpu::addInstruction("ADC A, (HL)", 8, 0, (void*)&GBemulator::Cpu::adc_A_HL_ind);
    instrMap[0x8f] = GBemulator::Cpu::addInstruction("ADC A, A", 4, 0, (void*)&GBemulator::Cpu::adc_A_A);

    //---------------------SUB------------------------------
    instrMap[0x90] = GBemulator::Cpu::addInstruction("SUB A, B", 4, 0, (void*)&GBemulator::Cpu::sub_A_B);
    instrMap[0x91] = GBemulator::Cpu::addInstruction("SUB A, C", 4, 0, (void*)&GBemulator::Cpu::sub_A_C);
    instrMap[0x92] = GBemulator::Cpu::addInstruction("SUB A, D", 4, 0, (void*)&GBemulator::Cpu::sub_A_D);
    instrMap[0x93] = GBemulator::Cpu::addInstruction("SUB A, E", 4, 0, (void*)&GBemulator::Cpu::sub_A_E);
    instrMap[0x94] = GBemulator::Cpu::addInstruction("SUB A, H", 4, 0, (void*)&GBemulator::Cpu::sub_A_H);
    instrMap[0x95] = GBemulator::Cpu::addInstruction("SUB A, L", 4, 0, (void*)&GBemulator::Cpu::sub_A_L);
    instrMap[0x96] = GBemulator::Cpu::addInstruction("SUB A, (HL)", 8, 0, (void*)&GBemulator::Cpu::sub_A_HL_ind);
    instrMap[0x97] = GBemulator::Cpu::addInstruction("SUB A, A", 4, 0, (void*)&GBemulator::Cpu::sub_A_A);

    //---------------------SBC------------------------------
    instrMap[0x98] = GBemulator::Cpu::addInstruction("SBC A, B", 4, 0, (void*)&GBemulator::Cpu::sbc_A_B);
    instrMap[0x99] = GBemulator::Cpu::addInstruction("SBC A, C", 4, 0, (void*)&GBemulator::Cpu::sbc_A_C);
    instrMap[0x9a] = GBemulator::Cpu::addInstruction("SBC A, D", 4, 0, (void*)&GBemulator::Cpu::sbc_A_D);
    instrMap[0x9b] = GBemulator::Cpu::addInstruction("SBC A, E", 4, 0, (void*)&GBemulator::Cpu::sbc_A_E);
    instrMap[0x9c] = GBemulator::Cpu::addInstruction("SBC A, H", 4, 0, (void*)&GBemulator::Cpu::sbc_A_H);
    instrMap[0x9d] = GBemulator::Cpu::addInstruction("SBC A, L", 4, 0, (void*)&GBemulator::Cpu::sbc_A_L);
    instrMap[0x9e] = GBemulator::Cpu::addInstruction("SBC A, (HL)", 8, 0, (void*)&GBemulator::Cpu::sbc_A_HL_ind);
    instrMap[0x9f] = GBemulator::Cpu::addInstruction("SBC A, A", 4, 0, (void*)&GBemulator::Cpu::sbc_A_A); */


    //std::cout<<instrMap[0x87].name<<'\t'<<instrMap[0x87].cycles<<'\t'<<instrMap[0x87].paramNum<<'\t'<<instrMap[0x87].function<<std::endl;

    //           ((void (*)(void))instrMap[0x87].function)();


}

void GBemulator::Cpu::loadInternalROM() {
    std::ifstream inFile(internalROMName, std::ifstream::ate | std::ifstream::binary);
    try {
        unsigned char t;
        for(int i = 0; i < internalROMSize; i++) {
            inFile >> std::hex >> t;
            intROM.push_back(t);
            //std::cout << std::hex << original[i];
        }
    }
    catch (const std::ifstream::failure& e) {
        std::cerr<<"Exception opening/reading file comparison.txt"<<std::endl;
        exit(1);
    }

    inFile.close();

}

bool GBemulator::Cpu::checkCartridge() {
    bool status = true;

    for(unsigned int i = 259; i <= 324; i++) { //0x103 = 259, 0x144 = 324
        BYTE read = mem.readByte(i);
        if(read != intROM[i])
            status = false;
    }
    if(!status)
        std::cerr<<"ROM not verified"<<std::endl;

    return status;
}

void GBemulator::Cpu::step() {
    BYTE instr = GBemulator::Cpu::fetch();
    instruction i = GBemulator::Cpu::decode(instr);
    execute(i);
}

void GBemulator::Cpu::reset() {
    //security check for original cartridge
    if(!GBemulator::Cpu::checkCartridge())
        //halt
        return;
    
    //initialization of special registers
    pc = 0x100;
    sp = 0xFFFE;

    //initialization of internal registers
    regAF.reg = 0x01B0;
    regBC.reg = 0x0013;
    regDE.reg = 0x00D8;
    regHL.reg = 0x014D;

    //fill the instructions map
    GBemulator::Cpu::fillInstructions();

    //initialization of I/O registers in the internal RAM
    mem.writeByte(0xFF05, 0x00);	//mem.writeByte
    mem.writeByte(0xFF06, 0x00);
    mem.writeByte(0xFF07, 0x00);
    mem.writeByte(0xFF10, 0x80);
    mem.writeByte(0xFF11, 0xBF);
    mem.writeByte(0xFF12, 0xF3);
    mem.writeByte(0xFF14, 0xBF);
    mem.writeByte(0xFF16, 0x3F);
    mem.writeByte(0xFF17, 0x00);
    mem.writeByte(0xFF19, 0xBF);
    mem.writeByte(0xFF1A, 0x7F);
    mem.writeByte(0xFF1B, 0xFF);
    mem.writeByte(0xFF1C, 0x9F);
    mem.writeByte(0xFF1E, 0xBF);
    mem.writeByte(0xFF20, 0xFF);
    mem.writeByte(0xFF21, 0x00);
    mem.writeByte(0xFF22, 0x00);
    mem.writeByte(0xFF23, 0xBF);
    mem.writeByte(0xFF24, 0x77);
    mem.writeByte(0xFF25, 0xF3);
    mem.writeByte(0xFF26, 0xF1);
    mem.writeByte(0xFF40, 0x91);
    mem.writeByte(0xFF42, 0x00);
    mem.writeByte(0xFF43, 0x00);
    mem.writeByte(0xFF45, 0x00);
    mem.writeByte(0xFF47, 0xFC);
    mem.writeByte(0xFF48, 0xFF);
    mem.writeByte(0xFF49, 0xFF);
    mem.writeByte(0xFF4A, 0x00);
    mem.writeByte(0xFF4B, 0x00);
    mem.writeByte(0xFFFF, 0x00);

}

BYTE GBemulator::Cpu::fetch(void) {
    unsigned char opcode = mem.readByte(pc);
    return opcode;
}

instruction GBemulator::Cpu::decode(BYTE opcode) {
    return instrMap[opcode];
}

void GBemulator::Cpu::execute(instruction i) {
    switch(i.paramNum) {
        case 0:
            ((void (*)(void))i.function)();
            break;
        default:
            return;
    }
}

//-----------------------ADD-------------------------------------
void GBemulator::Cpu::add(unsigned char n) {
    int res = regAF.high + (int) n;
    
    if(res == 0)        //sum = 0
        setFlag(flagZ);
    else
        resetFlag(flagZ);

    regAF.high = res;
    // if(res < 0)     //sum < 0
    //    setFlag(flagN);
    //else
    //    resetFlag(flagN);
        
    if(res > 255)  //sum overflow
        setFlag(flagC);
    else
        resetFlag(flagC);
        
    if(((n & 0x0F) + (regAF.high & 0x0F)) > 0x0F)    //if carry from bit 3
        setFlag(flagH);
    else
        resetFlag(flagH);
}
/* void GBemulator::Cpu::add_A_A(void) {
    GBemulator::Cpu::add(regAF.high);
}
void GBemulator::Cpu::add_A_B(void) {
    GBemulator::Cpu::add(regBC.high);
}
void GBemulator::Cpu::add_A_C(void) {
    GBemulator::Cpu::add(regBC.low);
}
void GBemulator::Cpu::add_A_D(void) {
    GBemulator::Cpu::add(regDE.high);
}
void GBemulator::Cpu::add_A_E(void) {
    GBemulator::Cpu::add(regDE.low);
}
void GBemulator::Cpu::add_A_H(void) {
    GBemulator::Cpu::add(regHL.high);
}
void GBemulator::Cpu::add_A_L(void) {
    GBemulator::Cpu::add(regHL.low);
} */
 void GBemulator::Cpu::add_A_HL_ind(void) {
    unsigned char n = mem.readByte(regHL.reg);
    GBemulator::Cpu::add(n);
}
void GBemulator::Cpu::add_A_n(unsigned char n) {
    GBemulator::Cpu::add(n);
}

//-----------------------ADC-------------------------------------
void GBemulator::Cpu::adc(unsigned char n) {
    int carry = isFlagCarry() ? 1 : 0;  //carry = 1 or 0
    GBemulator::Cpu::add(n + carry);
    /* int res = regAF.high + (int) n + carry;

    if(res == 0)        //sum = 0
        setFlag(flagZ);
    else
        resetFlag(flagZ);

    regAF.high = res;

    // if(res < 0)     //sum < 0
    //    setFlag(flagN);
    //else
    //    resetFlag(flagN);
        
    if(res > 255)  //sum overflow
        setFlag(flagC);
    else
        resetFlag(flagC);
        
    if(((n & 0x0F) + (regAF.high & 0x0F) + carry) > 0x0F)    //if carry from bit 3
        setFlag(flagH);
    else
        resetFlag(flagH); */
}
/* void GBemulator::Cpu::adc_A_A(void) {
    GBemulator::Cpu::adc(regAF.high);
} 
void GBemulator::Cpu::adc_A_B(void) {
    GBemulator::Cpu::adc(regBC.high);
}
void GBemulator::Cpu::adc_A_C(void) {
    GBemulator::Cpu::adc(regBC.low);
}
void GBemulator::Cpu::adc_A_D(void) {
    GBemulator::Cpu::adc(regDE.high);
}
void GBemulator::Cpu::adc_A_E(void) {
    GBemulator::Cpu::adc(regDE.low);
}
void GBemulator::Cpu::adc_A_H(void) {
    GBemulator::Cpu::adc(regHL.high);
}
void GBemulator::Cpu::adc_A_L(void) {
    GBemulator::Cpu::adc(regHL.low);
}*/
void GBemulator::Cpu::adc_A_HL_ind(void) {
    unsigned char n = mem.readByte(regHL.reg);
    GBemulator::Cpu::adc(n);
}
void GBemulator::Cpu::adc_A_n(unsigned char n) {
    GBemulator::Cpu::adc(n);
}

//-----------------------SUB-------------------------------------
void GBemulator::Cpu::sub(unsigned char n) {
    int res = regAF.high - (int) n;

    if(res == 0)        //sub = 0
        setFlag(flagZ);
    else
        resetFlag(flagZ);

    regAF.high = res;
    
    setFlag(flagN);
        
    if(res < 0)  //sub with borrow
        setFlag(flagC);
    else
        resetFlag(flagC);
        
    if(((n & 0x0F) + (regAF.high & 0x0F)) < 0)    //if borrow from bit 3
        setFlag(flagH);
    else
        resetFlag(flagH);
}
/* void GBemulator::Cpu::sub_A_A(void) {
    GBemulator::Cpu::sub(regAF.high);
}
void GBemulator::Cpu::sub_A_B(void) {
    GBemulator::Cpu::sub(regBC.high);
}
void GBemulator::Cpu::sub_A_C(void) {
    GBemulator::Cpu::sub(regBC.low);
}
void GBemulator::Cpu::sub_A_D(void) {
    GBemulator::Cpu::sub(regDE.high);
}
void GBemulator::Cpu::sub_A_E(void) {
    GBemulator::Cpu::sub(regDE.low);
}
void GBemulator::Cpu::sub_A_H(void) {
    GBemulator::Cpu::sub(regHL.high);
}
void GBemulator::Cpu::sub_A_L(void) {
    GBemulator::Cpu::sub(regHL.low);
} */
void GBemulator::Cpu::sub_A_HL_ind(void) {
    unsigned char n = mem.readByte(regHL.reg);
    GBemulator::Cpu::sub(n);
}
void GBemulator::Cpu::sub_A_n(unsigned char n) {
    GBemulator::Cpu::sub(n);
}

//-----------------------SBC-------------------------------------
void GBemulator::Cpu::sbc(unsigned char n) {
    int carry = isFlagCarry() ? 1 : 0;  //carry = 1 or 0
    GBemulator::Cpu::sub(n + carry);
    /* int res = regAF.high - ((int) n + carry);

    if(res == 0)        //sub = 0
        setFlag(flagZ);
    else
        resetFlag(flagZ);

    regAF.high = res;
    
    setFlag(flagN);
        
    if(res < 0)  //sub with borrow
        setFlag(flagC);
    else
        resetFlag(flagC);
        
    if(((n & 0x0F) + (regAF.high & 0x0F) + carry) < 0)    //if carry from bit 3
        setFlag(flagH);
    else
        resetFlag(flagH); */
}
/* void GBemulator::Cpu::sbc_A_A(void) {
    GBemulator::Cpu::sbc(regAF.high);
}
void GBemulator::Cpu::sbc_A_B(void) {
    GBemulator::Cpu::sbc(regBC.high);
}
void GBemulator::Cpu::sbc_A_C(void) {
    GBemulator::Cpu::sbc(regBC.low);
}
void GBemulator::Cpu::sbc_A_D(void) {
    GBemulator::Cpu::sbc(regDE.high);
}
void GBemulator::Cpu::sbc_A_E(void) {
    GBemulator::Cpu::sbc(regDE.low);
}
void GBemulator::Cpu::sbc_A_H(void) {
    GBemulator::Cpu::sbc(regHL.high);
}
void GBemulator::Cpu::sbc_A_L(void) {
    GBemulator::Cpu::sbc(regHL.low);
} */
void GBemulator::Cpu::sbc_A_HL_ind(void) {
    unsigned char n = mem.readByte(regHL.reg);
    GBemulator::Cpu::sbc(n);
}
/* void GBemulator::Cpu::sbc_A_n(unsigned char n) {
    GBemulator::Cpu::sbc(n);
} */
 
//-----------------------AND-------------------------------------
void GBemulator::Cpu::and_(unsigned char n) {
    int res = regAF.high & (int) n;

    if(res == 0)        //and = 0
        setFlag(flagZ);
    else
        resetFlag(flagZ);

    regAF.high = res;
    
    setFlag(flagH);
    resetFlag(flagC);
    resetFlag(flagN);
        
}
/* void GBemulator::Cpu::and_A_A(void) {
    GBemulator::Cpu::and_(regAF.high);
}
void GBemulator::Cpu::and_A_B(void) {
    GBemulator::Cpu::and_(regBC.high);
}
void GBemulator::Cpu::and_A_C(void) {
    GBemulator::Cpu::and_(regBC.low);
}
void GBemulator::Cpu::and_A_D(void) {
    GBemulator::Cpu::and_(regDE.high);
}
void GBemulator::Cpu::and_A_E(void) {
    GBemulator::Cpu::and_(regDE.low);
}
void GBemulator::Cpu::and_A_H(void) {
    GBemulator::Cpu::and_(regHL.high);
}
void GBemulator::Cpu::and_A_L(void) {
    GBemulator::Cpu::and_(regHL.low);
} */
void GBemulator::Cpu::and_A_HL_ind(void) {
    unsigned char n = mem.readByte(regHL.reg);
    GBemulator::Cpu::and_(n);
}
void GBemulator::Cpu::and_A_n(unsigned char n) {
    GBemulator::Cpu::and_(n);
}

//-----------------------OR-------------------------------------
void GBemulator::Cpu::or_(unsigned char n) {
    int res = regAF.high | (int) n;

    if(res == 0)        //or = 0
        setFlag(flagZ);
    else
        resetFlag(flagZ);

    regAF.high = res;
    
    resetFlag(flagH);
    resetFlag(flagC);
    resetFlag(flagN);
        
}
/* void GBemulator::Cpu::or_A_A(void) {
    GBemulator::Cpu::or_(regAF.high);
}
void GBemulator::Cpu::or_A_B(void) {
    GBemulator::Cpu::or_(regBC.high);
}
void GBemulator::Cpu::or_A_C(void) {
    GBemulator::Cpu::or_(regBC.low);
}
void GBemulator::Cpu::or_A_D(void) {
    GBemulator::Cpu::or_(regDE.high);
}
void GBemulator::Cpu::or_A_E(void) {
    GBemulator::Cpu::or_(regDE.low);
}
void GBemulator::Cpu::or_A_H(void) {
    GBemulator::Cpu::or_(regHL.high);
}
void GBemulator::Cpu::or_A_L(void) {
    GBemulator::Cpu::or_(regHL.low);
} */
void GBemulator::Cpu::or_A_HL_ind(void) {
    unsigned char n = mem.readByte(regHL.reg);
    GBemulator::Cpu::or_(n);
}
void GBemulator::Cpu::or_A_n(unsigned char n) {
    GBemulator::Cpu::or_(n);
}

//-----------------------XOR-------------------------------------
void GBemulator::Cpu::xor_(unsigned char n) {
    int res;
    res ? !n : n;

    if(res == 0)        //xor = 0
        setFlag(flagZ);
    else
        resetFlag(flagZ);

    regAF.high = res;
    
    resetFlag(flagH);
    resetFlag(flagC);
    resetFlag(flagN);
        
}
/* void GBemulator::Cpu::xor_A_A(void) {
    GBemulator::Cpu::xor_(regAF.high);
}
void GBemulator::Cpu::xor_A_B(void) {
    GBemulator::Cpu::xor_(regBC.high);
}
void GBemulator::Cpu::xor_A_C(void) {
    GBemulator::Cpu::xor_(regBC.low);
}
void GBemulator::Cpu::xor_A_D(void) {
    GBemulator::Cpu::xor_(regDE.high);
}
void GBemulator::Cpu::xor_A_E(void) {
    GBemulator::Cpu::xor_(regDE.low);
}
void GBemulator::Cpu::xor_A_H(void) {
    GBemulator::Cpu::xor_(regHL.high);
}
void GBemulator::Cpu::xor_A_L(void) {
    GBemulator::Cpu::xor_(regHL.low);
} */
void GBemulator::Cpu::xor_A_HL_ind(void) {
    unsigned char n = mem.readByte(regHL.reg);
    GBemulator::Cpu::xor_(n);
}
void GBemulator::Cpu::xor_A_n(unsigned char n) {
    GBemulator::Cpu::xor_(n);
}

//------------------------CP-------------------------------------
void GBemulator::Cpu::cp(unsigned char n) {
    int res = regAF.high - (int) n;

    if(res == 0)        //sub = 0
        setFlag(flagZ);
    else
        resetFlag(flagZ);
    
    setFlag(flagN);
        
    if(res < 0)  //sub with borrow
        setFlag(flagC);
    else
        resetFlag(flagC);
        
    if(((n & 0x0F) + (regAF.high & 0x0F)) < 0)    //if borrow from bit 3
        setFlag(flagH);
    else
        resetFlag(flagH);
}
/* void GBemulator::Cpu::cp_A_A(void) {
    GBemulator::Cpu::cp(regAF.high);
}
void GBemulator::Cpu::cp_A_B(void) {
    GBemulator::Cpu::cp(regBC.high);
}
void GBemulator::Cpu::cp_A_C(void) {
    GBemulator::Cpu::cp(regBC.low);
}
void GBemulator::Cpu::cp_A_D(void) {
    GBemulator::Cpu::cp(regDE.high);
}
void GBemulator::Cpu::cp_A_E(void) {
    GBemulator::Cpu::cp(regDE.low);
}
void GBemulator::Cpu::cp_A_H(void) {
    GBemulator::Cpu::cp(regHL.high);
}
void GBemulator::Cpu::cp_A_L(void) {
    GBemulator::Cpu::cp(regHL.low);
} */
void GBemulator::Cpu::cp_A_HL_ind(void) {
    unsigned char n = mem.readByte(regHL.reg);
    GBemulator::Cpu::cp(n);
}
void GBemulator::Cpu::cp_A_n(unsigned char n) {
    GBemulator::Cpu::cp(n);
}

//------------------------INC-------------------------------------
void GBemulator::Cpu::inc(unsigned char* reg) {
    int res = (*reg) + 1;
    (*reg)++;

    if(res == 0)        //res = 0
        setFlag(flagZ);
    else
        resetFlag(flagZ);
    
    resetFlag(flagN);
        
    if((res & 0x0F) > 0x0F)    //if carry from bit 3
        setFlag(flagH);
    else
        resetFlag(flagH);
}
/*void GBemulator::Cpu::inc_A(void) {
    GBemulator::Cpu::inc(&regAF.high);
}
void GBemulator::Cpu::inc_B(void) {
    GBemulator::Cpu::inc(&regBC.high);
}
void GBemulator::Cpu::inc_C(void) {
    GBemulator::Cpu::inc(&regBC.low);
}
void GBemulator::Cpu::inc_D(void) {
    GBemulator::Cpu::inc(&regDE.high);
}
void GBemulator::Cpu::inc_E(void) {
    GBemulator::Cpu::inc(&regDE.low);
}
void GBemulator::Cpu::inc_H(void) {
    GBemulator::Cpu::inc(&regHL.high);
}
void GBemulator::Cpu::inc_L(void) {
    GBemulator::Cpu::inc(&regHL.low);
}*/
void GBemulator::Cpu::inc_HL_ind(void) {
    BYTE addr = mem.readByte(regHL.reg);
    BYTE val = mem.readByte(addr) + 1;
    mem.writeByte(addr, val);
    //ATTENZIONE, da rifare perchè così non aggiorna i flag---------------------------------
}

//------------------------DEC-------------------------------------
void GBemulator::Cpu::dec(unsigned char* reg) {
    int res = (*reg) - 1;
    (*reg)--;

    if(res == 0)        //res = 0
        setFlag(flagZ);
    else
        resetFlag(flagZ);
    
    setFlag(flagN);
        
    if((res & 0x0F) < 0)    //if borrow from bit 3
        setFlag(flagH);
    else
        resetFlag(flagH);
}
/* void GBemulator::Cpu::dec_A(void) {
    GBemulator::Cpu::dec(&regAF.high);
}
void GBemulator::Cpu::dec_B(void) {
    GBemulator::Cpu::dec(&regBC.high);
}
void GBemulator::Cpu::dec_C(void) {
    GBemulator::Cpu::dec(&regBC.low);
}
void GBemulator::Cpu::dec_D(void) {
    GBemulator::Cpu::dec(&regDE.high);
}
void GBemulator::Cpu::dec_E(void) {
    GBemulator::Cpu::dec(&regDE.low);
}
void GBemulator::Cpu::dec_H(void) {
    GBemulator::Cpu::dec(&regHL.high);
}
void GBemulator::Cpu::dec_L(void) {
    GBemulator::Cpu::dec(&regHL.low);
} */
void GBemulator::Cpu::dec_HL_ind(void) {
    //unsigned char n = mem.readByte(regHL.reg);
    //GBemulator::Cpu::dec(n);
    BYTE addr = mem.readByte(regHL.reg);
    BYTE val = mem.readByte(addr) - 1;
    mem.writeByte(addr, val);
}


//-----------------------ADD HL-------------------------------------
void GBemulator::Cpu::addWord(unsigned short n) {
    WORD res = regHL.reg + (int) n;   
    regAF.reg = res;
    resetFlag(flagN);
}
void GBemulator::Cpu::add_HL_BC(void) {
    GBemulator::Cpu::addWord(regBC.reg);
}
void GBemulator::Cpu::add_HL_DE(void) {
    GBemulator::Cpu::addWord(regDE.reg);
}
void GBemulator::Cpu::add_HL_HL(void) {
    GBemulator::Cpu::addWord(regHL.reg);
}
void GBemulator::Cpu::add_HL_SP(void) {
    GBemulator::Cpu::addWord(sp);
}
//-----------------------ADD SP-------------------------------------
void GBemulator::Cpu::add_SP_n(signed char n) {
   sp += (int) n;
}

//------------------------INC-------------------------------------
/* void GBemulator::Cpu::incWord(unsigned char* reg) {
    (*reg)++;
} */
void GBemulator::Cpu::inc_BC(void) {
    regBC.reg++;
    //GBemulator::Cpu::incWord(&regBC.reg);
}
void GBemulator::Cpu::inc_DE(void) {
    regBC.reg++;
    //GBemulator::Cpu::incWord(&regDE.reg);
}
void GBemulator::Cpu::inc_HL(void) {
    regBC.reg++;
    //GBemulator::Cpu::incWord(&regHL.reg);
}
void GBemulator::Cpu::inc_SP(void) {
    sp++;
}

//------------------------DEC-------------------------------------
/* void GBemulator::Cpu::decWord(unsigned char* reg) {
    (*reg)--;
} */
void GBemulator::Cpu::dec_BC(void) {
    regBC.reg--;
    //GBemulator::Cpu::decWord(&regBC.reg);
}
void GBemulator::Cpu::dec_DE(void) {
    regDE.reg--;
    //GBemulator::Cpu::decWord(&regDE.reg);
}
void GBemulator::Cpu::dec_HL(void) {
    regHL.reg--;
    //GBemulator::Cpu::decWord(&regHL.reg);
}
void GBemulator::Cpu::dec_SP(void) {
    sp--;
}
