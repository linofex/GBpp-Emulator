#include "../includes/cpu.hpp"
#include <iostream>
#include <map>
#include <string>

using namespace std;

Cpu::Cpu(void) { 
    reset();
}
Cpu::~Cpu(void) {
    exit(1);
}

/* instruction Cpu::makeInstructions(std::string name, int cycles, int paramNum, void* function) {
    instruction i = {name, cycles, paramNum};
    //instruction i = {name, cycles, paramNum, function};
    //cout<<i.name<<'\t'<<i.cycles<<'\t'<<i.function<<endl;
    cout<<"______________"<<endl;
    return i;
}  */

void Cpu::addInstructions() {
    instruction i = {"ADD A, n", 4, 0, Cpu::add_A_n};
    instrMap[0x80] =  i;
}
void Cpu::fillInstructions(string name, unsigned char cycles, void* function) {
    //instrMap[0x88] = {name, cycles, fun};
    //instrMap.insert{key = opcode, value =(name, cycles, function())};
    
    //instruction i = Cpu::makeInstructions("ADD A, B", 4, 0, Cpu::add_A_B);
    //instrMap[0x80] = i;

    //---------------------ADD------------------------------
    /*instrMap[0x80] = {"ADD A, B", 4, Cpu::add_A_B};
    instrMap[0x81] = {"ADD A, C", 4, add_A_C};
    instrMap[0x82] = {"ADD A, D", 4, add_A_D};
    instrMap[0x83] = {"ADD A, E", 4, add_A_E};
    instrMap[0x84] = {"ADD A, H", 4, add_A_H};
    instrMap[0x85] = {"ADD A, L", 4, add_A_L};
    instrMap[0x86] = {"ADD A, (HL)", 8, add_A_HL_ind};
    instrMap[0x87] = {"ADD A, A", 4, add_A_A};

    //---------------------ADC------------------------------
    instrMap[0x88] = {"ADC A, B", 4, adc_A_B};
    instrMap[0x89] = {"ADC A, C", 4, adc_A_C};
    instrMap[0x8a] = {"ADC A, D", 4, adc_A_D};
    instrMap[0x8b] = {"ADC A, E", 4, adc_A_E};
    instrMap[0x8c] = {"ADC A, H", 4, adc_A_H};
    instrMap[0x8d] = {"ADC A, L", 4, adc_A_L};
    instrMap[0x8e] = {"ADC A, (HL)", 8, adc_A_HL_ind};
    instrMap[0x8f] = {"ADC A, A", 4, adc_A_A};

    //---------------------SUB------------------------------
    instrMap[0x90] = {"SUB A, B", 4, sub_A_B};
    instrMap[0x91] = {"SUB A, C", 4, sub_A_C};
    instrMap[0x92] = {"SUB A, D", 4, sub_A_D};
    instrMap[0x93] = {"SUB A, E", 4, sub_A_E};
    instrMap[0x94] = {"SUB A, H", 4, sub_A_H};
    instrMap[0x95] = {"SUB A, L", 4, sub_A_L};
    instrMap[0x96] = {"SUB A, (HL)", 8, sub_A_HL_ind};
    instrMap[0x97] = {"SUB A, A", 4, sub_A_A};

    //---------------------SBC------------------------------
    instrMap[0x98] = {"SBC A, B", 4, sbc_A_B};
    instrMap[0x99] = {"SBC A, C", 4, sbc_A_C};
    instrMap[0x9a] = {"SBC A, D", 4, sbc_A_D};
    instrMap[0x9b] = {"SBC A, E", 4, sbc_A_E};
    instrMap[0x9c] = {"SBC A, H", 4, sbc_A_H};
    instrMap[0x9d] = {"SBC A, L", 4, sbc_A_L};
    instrMap[0x9e] = {"SBC A, (HL)", 8, sbc_A_HL_ind};
    instrMap[0x9f] = {"SBC A, A", 4, sbc_A_A};
    */

    //instrMap.insert{0x80, ("ADD A, B", 4, add_A_B)};
    //instrMap.insert{0x81, ("ADD A, C", 4, add_A_C)};
 //   instrMap.insert{0x82, ("ADD A, D", 4, add_A_D)};
 //   instrMap.insert{0x83, ("ADD A, E", 4, add_A_E)};
  //  instrMap.insert{0x84, ("ADD A, H", 4, add_A_H)};
  //  instrMap.insert{0x85, ("ADD A, L", 4, add_A_L)};
 //   instrMap.insert{0x86, ("ADD A, (HL)", 8, add_A_HL_ind)};
 //   instrMap.insert{0x87, ("ADD A, A", 4, add_A_A)};

    //---------------------ADC------------------------------
    /* instrMap.insert{0x88, ("ADC A, B", 4, adc_A_B)};
    instrMap.insert{0x89, ("ADC A, C", 4, adc_A_C)};
    instrMap.insert{0x8a, ("ADC A, D", 4, adc_A_D)};
    instrMap.insert{0x8b, ("ADC A, E", 4, adc_A_E)};
    instrMap.insert{0x8c, ("ADC A, H", 4, adc_A_H)};
    instrMap.insert{0x8d, ("ADC A, L", 4, adc_A_L)};
    instrMap.insert{0x8e, ("ADC A, (HL)", 8, adc_A_HL_ind)};
    instrMap.insert{0x8f, ("ADC A, A", 4, adc_A_A)}; 

    //---------------------SUB------------------------------
    instrMap.insert{0x90, ("SUB A, B", 4, sub_A_B)};
    instrMap.insert{0x91, ("SUB A, C", 4, sub_A_C)};
    instrMap.insert{0x92, ("SUB A, D", 4, sub_A_D)};
    instrMap.insert{0x93, ("SUB A, E", 4, sub_A_E)};
    instrMap.insert{0x94, ("SUB A, H", 4, sub_A_H)};
    instrMap.insert{0x95, ("SUB A, L", 4, sub_A_L)};
    instrMap.insert{0x96, ("SUB A, (HL)", 8, sub_A_HL_ind)};
    instrMap.insert{0x97, ("SUB A, A", 4, sub_A_A)};

    //---------------------SBC------------------------------
    instrMap.insert{0x98, ("SBC A, B", 4, sbc_A_B)};
    instrMap.insert{0x99, ("SBC A, C", 4, sbc_A_C)};
    instrMap.insert{0x9a, ("SBC A, D", 4, sbc_A_D)};
    instrMap.insert{0x9b, ("SBC A, E", 4, sbc_A_E)};
    instrMap.insert{0x9c, ("SBC A, H", 4, sbc_A_H)};
    instrMap.insert{0x9d, ("SBC A, L", 4, sbc_A_L)};
    instrMap.insert{0x9e, ("SBC A, (HL)", 8, sbc_A_HL_ind)};
    instrMap.insert{0x9f, ("SBC A, A", 4, sbc_A_A)};
    */

    //cout<<instrMap[0x88].name<<'\t'<<instrMap[0x88].cycles<<'\t'<<instrMap[0x88].fun<<endl;
    
    
    //{ "ADC B", 0, adc_A_B },                       // 0x88
	//{ "ADC C", 0, adc_A_C },                       // 0x89
	//{ "ADC D", 0, adc_A_D },                       // 0x8a
	//{ "ADC E", 0, adc_A_E },                       // 0x8b
	//{ "ADC H", 0, adc_A_H },                       // 0x8c
	//{ "ADC L", 0, adc_A_L },                       // 0x8d
	//{ "ADC (HL)", 0, adc_A_HL_ind },               // 0x8e
	//{ "ADC A", 0, adc_A_A},                        // 0x8f

}

bool Cpu::checkCartridge() {
    /*
    const char *fn = "comparison.txt";
    ifstream infile(fn, fstream::in);

    unsigned char original[48] = {};

    try {
        //fn.open("comparison.txt");
        for(int i = 0; i < lenght; i++) {
            infile >> hex >> original[i];
            cout << hex << a;
        }
    }
    catch (const ifstream::failure& e) {
        cerr<< "Exception opening/reading file comparison.txt"<endl;
        return false;
    }

    inFile.close();
    return true;
    */
}

void Cpu::step() {
    BYTE instr = Cpu::fetch();
    Cpu::decode(instr);
    //switch case to select the version with 0, 1 or 2 parameters

}

void Cpu::reset() {
    //security check for original cartridge
    if(!Cpu::checkCartridge())
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

    /* //initialization of I/O registers in the internal RAM
    wb(0xFF05, 0x00);	//writeByte
    wb(0xFF06, 0x00);
    wb(0xFF07, 0x00);
    wb(0xFF10, 0x80);
    wb(0xFF11, 0xBF);
    wb(0xFF12, 0xF3);
    wb(0xFF14, 0xBF);
    wb(0xFF16, 0x3F);
    wb(0xFF17, 0x00);
    wb(0xFF19, 0xBF);
    wb(0xFF1A, 0x7F);
    wb(0xFF1B, 0xFF);
    wb(0xFF1C, 0x9F);
    wb(0xFF1E, 0xBF);
    wb(0xFF20, 0xFF);
    wb(0xFF21, 0x00);
    wb(0xFF22, 0x00);
    wb(0xFF23, 0xBF);
    wb(0xFF24, 0x77);
    wb(0xFF25, 0xF3);
    wb(0xFF26, 0xF1);
    wb(0xFF40, 0x91);
    wb(0xFF42, 0x00);
    wb(0xFF43, 0x00);
    wb(0xFF45, 0x00);
    wb(0xFF47, 0xFC);
    wb(0xFF48, 0xFF);
    wb(0xFF49, 0xFF);
    wb(0xFF4A, 0x00);
    wb(0xFF4B, 0x00);
    wb(0xFFFF, 0x00); */

}

BYTE Cpu::fetch(void) {
    //unsigned char opcode = readByte(pc);
    //return opcode;
}

void* Cpu::decode(BYTE opcode) {
    //return instrMap[opcode].function;
}

void Cpu::execute(void* exec) {
    //exec();
    
}

//-----------------------ADD-------------------------------------
void Cpu::add(unsigned char n) {
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
void Cpu::add_A_A(void) {
    Cpu::add(regAF.high);
}
void Cpu::add_A_B(void) {
    Cpu::add(regBC.high);
}
void Cpu::add_A_C(void) {
    Cpu::add(regBC.low);
}
void Cpu::add_A_D(void) {
    Cpu::add(regDE.high);
}
void Cpu::add_A_E(void) {
    Cpu::add(regDE.low);
}
void Cpu::add_A_H(void) {
    Cpu::add(regHL.high);
}
void Cpu::add_A_L(void) {
    Cpu::add(regHL.low);
}
 void Cpu::add_A_HL_ind(void) {
    //unsigned char n = rb(regHL.reg)      //readByte
    //Cpu::add(n);
}
void Cpu::add_A_n(unsigned char n) {
    Cpu::add(n);
}

//-----------------------ADC-------------------------------------
void Cpu::adc(unsigned char n) {
    int carry = isFlagCarry() ? 1 : 0;  //carry = 1 or 0
    Cpu::add(n + carry);
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
void Cpu::adc_A_A(void) {
    Cpu::adc(regAF.high);
}
void Cpu::adc_A_B(void) {
    Cpu::adc(regBC.high);
}
void Cpu::adc_A_C(void) {
    Cpu::adc(regBC.low);
}
void Cpu::adc_A_D(void) {
    Cpu::adc(regDE.high);
}
void Cpu::adc_A_E(void) {
    Cpu::adc(regDE.low);
}
void Cpu::adc_A_H(void) {
    Cpu::adc(regHL.high);
}
void Cpu::adc_A_L(void) {
    Cpu::adc(regHL.low);
}
void Cpu::adc_A_HL_ind(void) {
    //unsigned char n = rb(regHL.reg)      //readByte
    //Cpu::adc(n);
}
void Cpu::adc_A_n(unsigned char n) {
    Cpu::adc(n);
}

//-----------------------SUB-------------------------------------
void Cpu::sub(unsigned char n) {
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
void Cpu::sub_A_A(void) {
    Cpu::sub(regAF.high);
}
void Cpu::sub_A_B(void) {
    Cpu::sub(regBC.high);
}
void Cpu::sub_A_C(void) {
    Cpu::sub(regBC.low);
}
void Cpu::sub_A_D(void) {
    Cpu::sub(regDE.high);
}
void Cpu::sub_A_E(void) {
    Cpu::sub(regDE.low);
}
void Cpu::sub_A_H(void) {
    Cpu::sub(regHL.high);
}
void Cpu::sub_A_L(void) {
    Cpu::sub(regHL.low);
}
void Cpu::sub_A_HL_ind(void) {
    //unsigned char n = rb(regHL.reg)      //readByte
    //Cpu::sub(n);
}
void Cpu::sub_A_n(unsigned char n) {
    Cpu::sub(n);
}

//-----------------------SBC-------------------------------------
void Cpu::sbc(unsigned char n) {
    int carry = isFlagCarry() ? 1 : 0;  //carry = 1 or 0
    Cpu::sub(n + carry);
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
void Cpu::sbc_A_A(void) {
    Cpu::sbc(regAF.high);
}
void Cpu::sbc_A_B(void) {
    Cpu::sbc(regBC.high);
}
void Cpu::sbc_A_C(void) {
    Cpu::sbc(regBC.low);
}
void Cpu::sbc_A_D(void) {
    Cpu::sbc(regDE.high);
}
void Cpu::sbc_A_E(void) {
    Cpu::sbc(regDE.low);
}
void Cpu::sbc_A_H(void) {
    Cpu::sbc(regHL.high);
}
void Cpu::sbc_A_L(void) {
    Cpu::sbc(regHL.low);
}
void Cpu::sbc_A_HL_ind(void) {
    //unsigned char n = rb(regHL.reg)      //readByte
    //Cpu::sbc(n);
}
/* void Cpu::sbc_A_n(unsigned char n) {
    Cpu::sbc(n);
} */
 
//-----------------------AND-------------------------------------
void Cpu::and_(unsigned char n) {
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
void Cpu::and_A_A(void) {
    Cpu::and_(regAF.high);
}
void Cpu::and_A_B(void) {
    Cpu::and_(regBC.high);
}
void Cpu::and_A_C(void) {
    Cpu::and_(regBC.low);
}
void Cpu::and_A_D(void) {
    Cpu::and_(regDE.high);
}
void Cpu::and_A_E(void) {
    Cpu::and_(regDE.low);
}
void Cpu::and_A_H(void) {
    Cpu::and_(regHL.high);
}
void Cpu::and_A_L(void) {
    Cpu::and_(regHL.low);
}
void Cpu::and_A_HL_ind(void) {
    //unsigned char n = rb(regHL.reg)      //readByte
    //Cpu::and_(n);
}
void Cpu::and_A_n(unsigned char n) {
    Cpu::and_(n);
}

//-----------------------OR-------------------------------------
void Cpu::or_(unsigned char n) {
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
void Cpu::or_A_A(void) {
    Cpu::or_(regAF.high);
}
void Cpu::or_A_B(void) {
    Cpu::or_(regBC.high);
}
void Cpu::or_A_C(void) {
    Cpu::or_(regBC.low);
}
void Cpu::or_A_D(void) {
    Cpu::or_(regDE.high);
}
void Cpu::or_A_E(void) {
    Cpu::or_(regDE.low);
}
void Cpu::or_A_H(void) {
    Cpu::or_(regHL.high);
}
void Cpu::or_A_L(void) {
    Cpu::or_(regHL.low);
}
void Cpu::or_A_HL_ind(void) {
    //unsigned char n = rb(regHL.reg)      //readByte
    //Cpu::or_(n);
}
void Cpu::or_A_n(unsigned char n) {
    Cpu::or_(n);
}

//-----------------------XOR-------------------------------------
void Cpu::xor_(unsigned char n) {
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
void Cpu::xor_A_A(void) {
    Cpu::xor_(regAF.high);
}
void Cpu::xor_A_B(void) {
    Cpu::xor_(regBC.high);
}
void Cpu::xor_A_C(void) {
    Cpu::xor_(regBC.low);
}
void Cpu::xor_A_D(void) {
    Cpu::xor_(regDE.high);
}
void Cpu::xor_A_E(void) {
    Cpu::xor_(regDE.low);
}
void Cpu::xor_A_H(void) {
    Cpu::xor_(regHL.high);
}
void Cpu::xor_A_L(void) {
    Cpu::xor_(regHL.low);
}
void Cpu::xor_A_HL_ind(void) {
    //unsigned char n = rb(regHL.reg)      //readByte
    //Cpu::xor_(n);
}
void Cpu::xor_A_n(unsigned char n) {
    Cpu::xor_(n);
}

//------------------------CP-------------------------------------
void Cpu::cp(unsigned char n) {
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
void Cpu::cp_A_A(void) {
    Cpu::cp(regAF.high);
}
void Cpu::cp_A_B(void) {
    Cpu::cp(regBC.high);
}
void Cpu::cp_A_C(void) {
    Cpu::cp(regBC.low);
}
void Cpu::cp_A_D(void) {
    Cpu::cp(regDE.high);
}
void Cpu::cp_A_E(void) {
    Cpu::cp(regDE.low);
}
void Cpu::cp_A_H(void) {
    Cpu::cp(regHL.high);
}
void Cpu::cp_A_L(void) {
    Cpu::cp(regHL.low);
}
void Cpu::cp_A_HL_ind(void) {
    //unsigned char n = rb(regHL.reg)      //readByte
    //Cpu::cp(n);
}
void Cpu::cp_A_n(unsigned char n) {
    Cpu::cp(n);
}

//------------------------INC-------------------------------------
void Cpu::inc(unsigned char* reg) {
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
void Cpu::inc_A(void) {
    Cpu::inc(&regAF.high);
}
void Cpu::inc_B(void) {
    Cpu::inc(&regBC.high);
}
void Cpu::inc_C(void) {
    Cpu::inc(&regBC.low);
}
void Cpu::inc_D(void) {
    Cpu::inc(&regDE.high);
}
void Cpu::inc_E(void) {
    Cpu::inc(&regDE.low);
}
void Cpu::inc_H(void) {
    Cpu::inc(&regHL.high);
}
void Cpu::inc_L(void) {
    Cpu::inc(&regHL.low);
}
void inc_HL_ind(void) {
    //unsigned char n = rb(regHL.reg)      //readByte
    //Cpu::inc(n);
}

//------------------------DEC-------------------------------------
void Cpu::dec(unsigned char* reg) {
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
void Cpu::dec_A(void) {
    Cpu::dec(&regAF.high);
}
void Cpu::dec_B(void) {
    Cpu::dec(&regBC.high);
}
void Cpu::dec_C(void) {
    Cpu::dec(&regBC.low);
}
void Cpu::dec_D(void) {
    Cpu::dec(&regDE.high);
}
void Cpu::dec_E(void) {
    Cpu::dec(&regDE.low);
}
void Cpu::dec_H(void) {
    Cpu::dec(&regHL.high);
}
void Cpu::dec_L(void) {
    Cpu::dec(&regHL.low);
}
void Cpu::dec_HL_ind(void) {
    //unsigned char n = rb(regHL.reg)      //readByte
    //Cpu::dec(n);
}


//-----------------------ADD HL-------------------------------------
void Cpu::addWord(unsigned short n) {
    WORD res = regHL.reg + (int) n;   
    regAF.reg = res;
    resetFlag(flagN);
}
void Cpu::add_HL_BC(void) {
    Cpu::addWord(regBC.reg);
}
void Cpu::add_HL_DE(void) {
    Cpu::addWord(regDE.reg);
}
void Cpu::add_HL_HL(void) {
    Cpu::addWord(regHL.reg);
}
void Cpu::add_HL_SP(void) {
    Cpu::addWord(sp);
}
//-----------------------ADD SP-------------------------------------
void Cpu::add_SP_n(signed char n) {
   sp += (int) n;
}

//------------------------INC-------------------------------------
/* void Cpu::incWord(unsigned char* reg) {
    (*reg)++;
} */
void Cpu::inc_BC(void) {
    regBC.reg++;
    //Cpu::incWord(&regBC.reg);
}
void Cpu::inc_DE(void) {
    regBC.reg++;
    //Cpu::incWord(&regDE.reg);
}
void Cpu::inc_HL(void) {
    regBC.reg++;
    //Cpu::incWord(&regHL.reg);
}
void Cpu::inc_SP(void) {
    sp++;
}

//------------------------DEC-------------------------------------
/* void Cpu::decWord(unsigned char* reg) {
    (*reg)--;
} */
void Cpu::dec_BC(void) {
    regBC.reg--;
    //Cpu::decWord(&regBC.reg);
}
void Cpu::dec_DE(void) {
    regDE.reg--;
    //Cpu::decWord(&regDE.reg);
}
void Cpu::dec_HL(void) {
    regHL.reg--;
    //Cpu::decWord(&regHL.reg);
}
void Cpu::dec_SP(void) {
    sp--;
}
