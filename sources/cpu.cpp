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
    mem = m;
    Cpu::reset();
    std::cout<<"reset end"<<std::endl;
}
Cpu::~Cpu(void) {
    std::cout << "CPU distruttore\n";
    //exit(1);
}

void Cpu::initInstructions() {
    init(instrSet);
}


void Cpu::step() {
    
    unsigned char opcode = 0x80;//mem->readByte(pc);
   
    //std::cout<<i.name<<'\t'<<i.cycles<<'\t'<<i.paramNum<<'\t'<<i.function<<std::endl;

    //BYTE opcode = Cpu::fetch();
    instruction instr = Cpu::decode(opcode);
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

    clockCycles = 0;
    timerCounter = 1024;
    hostOldTime = std::chrono::system_clock::now();
    targetOldTime = TARGETPERIOD * clockCycles;
    
    Cpu::step();
}

BYTE Cpu::fetch(void) {
    std::cout<<"fetch"<<std::endl;
    unsigned char opcode = 0x80;//mem->readByte(pc);
    return opcode;
}

struct instruction Cpu::decode(BYTE opcode) {
    std::cout<<"decode"<<std::endl;
    std::cout<<"---------------------------------------------> "<<instrSet.size()<<std::endl;
    return instrSet.at(0x80);
}

void Cpu::execute(instruction instr) {
    std::cout<<"execute"<<std::endl;
    instr.function(this);

    //update the clock cycles counter
    clockCycles += instr.cycles;

    Cpu::updateTimers(instr.cycles);
    Cpu::sync();

    //check for interrupts >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
}

void Cpu::updateTimers(int cycles) {
    Cpu::stepTimer(cycles);
    Cpu::stepDivider(cycles);
}

bool Cpu::isTimerOn() {
    BYTE tmc = mem->readByte(TMC);
    return ((tmc >> 2) & 1);
}

void Cpu::setTimer() {
    
    if(!isTimerOn())
        return;

    int oldTimer = mem->readByte(TMC);   //timer controller register
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
            exit(1);
            std::cout<<"Invalid timer"<<std::endl;
            break; 
    }

    timerCounter = newTimer;
}

void Cpu::stepDivider(int cycles) {
    
    //divider always done
    dividerCounter += cycles;
    
    if(dividerCounter >= 0xFF) {   //next is an overflow (255)
        dividerCounter = 0x00;
        mem->writeByte(DIVIDER, dividerCounter);
    }
}

void Cpu::stepTimer(int cycles) {
    
    if(!isTimerOn())
        return;

    timerCounter -= cycles;
    if(timerCounter <= 0) {
        //timer is reset again to the value specified by the timer controller TMC
        Cpu::setTimer();
        BYTE tima = mem->readByte(TIMA);

        if(tima == 0xFF) {              //next is an overflow (255)
            BYTE tma = mem->readByte(TMA);
            mem->writeByte(TIMA, tma);

            //send timer interrupt ______________________________>>>>>>>>>>>>>>>>>>>>>>>>

        } else {            //increment the counter
            mem->writeByte(TIMA, tima + 1);
        }
    }
}

void Cpu::sync() {

    std::chrono::time_point<std::chrono::system_clock>hostNewTime = std::chrono::system_clock::now();
    std::chrono::duration<double> hostElapsedTimeC = hostNewTime - hostOldTime;
    unsigned int hostElapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(hostElapsedTimeC).count();
    std::cout<<"The host elapsed time is: "<<'\t'<<hostElapsedTime<<std::endl;

    unsigned int targetNewTime = TARGETPERIOD * clockCycles;
    unsigned int targetElapsedTime = targetNewTime - targetOldTime;
    std::cout<<"The target elapsed time is: "<<'\t'<<targetElapsedTime<<std::endl;
    

    if((targetElapsedTime - hostElapsedTime) > (2/10^3))     //2 ms
        std::cout<<"The diff is: "<<'\t'<<targetElapsedTime - hostElapsedTime<<std::endl;
        //Sleep(diff);

    hostOldTime = hostNewTime;
    targetOldTime = targetNewTime;
 
}

void Cpu::push(WORD t_val) {
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

/* 
//-----------------------ADD-------------------------------------
/*void Cpu::add(unsigned char n) {
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
    unsigned char n = mem->readByte(regHL.reg);
    Cpu::add(n);
}
void Cpu::add_A_n(unsigned char n) {
    Cpu::add(n);
}
*/
//-----------------------ADC-------------------------------------
/*void Cpu::adc(unsigned char n) {
    int carry = isFlagCarry() ? 1 : 0;  //carry = 1 or 0
    //Cpu::add(n + carry);
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
        resetFlag(flagH); 
}
/* void Cpu::adc_A_A(void) {
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
    unsigned char n = mem->readByte(regHL.reg);
    Cpu::adc(n);
}
void Cpu::adc_A_n(unsigned char n) {
    Cpu::adc(n);
}
*/
//-----------------------SUB-------------------------------------
/*void Cpu::sub(unsigned char n) {
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
}*/
/* void Cpu::sub_A_A(void) {
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
    unsigned char n = mem->readByte(regHL.reg);
    Cpu::sub(n);
}
void Cpu::sub_A_n(unsigned char n) {
    Cpu::sub(n);
}*/

//-----------------------SBC-------------------------------------
/*void Cpu::sbc(unsigned char n) {
    int carry = isFlagCarry() ? 1 : 0;  //carry = 1 or 0
    //Cpu::sub(n + carry);
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
        resetFlag(flagH); 
}
/* void Cpu::sbc_A_A(void) {
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
    unsigned char n = mem->readByte(regHL.reg);
    Cpu::sbc(n);
}
/* void Cpu::sbc_A_n(unsigned char n) {
    Cpu::sbc(n);
} */
 
//-----------------------AND-------------------------------------
/*void Cpu::and_(unsigned char n) {
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
/* void Cpu::and_A_A(void) {
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
    unsigned char n = mem->readByte(regHL.reg);
    Cpu::and_(n);
}
void Cpu::and_A_n(unsigned char n) {
    Cpu::and_(n);
}*/

//-----------------------OR-------------------------------------
/*void Cpu::or_(unsigned char n) {
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
/* void Cpu::or_A_A(void) {
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
    unsigned char n = mem->readByte(regHL.reg);
    Cpu::or_(n);
}
void Cpu::or_A_n(unsigned char n) {
    Cpu::or_(n);
}*/

//-----------------------XOR-------------------------------------
/*void Cpu::xor_(unsigned char n) {
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
/* void Cpu::xor_A_A(void) {
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
    unsigned char n = mem->readByte(regHL.reg);
    Cpu::xor_(n);
}
void Cpu::xor_A_n(unsigned char n) {
    Cpu::xor_(n);
}
*/
//------------------------CP-------------------------------------
/*void Cpu::cp(unsigned char n) {
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
/* void Cpu::cp_A_A(void) {
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
    unsigned char n = mem->readByte(regHL.reg);
    Cpu::cp(n);
}
void Cpu::cp_A_n(unsigned char n) {
    Cpu::cp(n);
}*/

//------------------------INC-------------------------------------
/*void Cpu::inc(unsigned char* reg) {
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
/*void Cpu::inc_A(void) {
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
void Cpu::inc_HL_ind(void) {
    BYTE addr = mem->readByte(regHL.reg);
    BYTE val = mem->readByte(addr) + 1;
    mem->writeByte(addr, val);
    //ATTENZIONE, da rifare perchè così non aggiorna i flag---------------------------------
}
*/
//------------------------DEC-------------------------------------
/*void Cpu::dec(unsigned char* reg) {
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
/* void Cpu::dec_A(void) {
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
    //unsigned char n = mem->readByte(regHL.reg);
    //Cpu::dec(n);
    BYTE addr = mem->readByte(regHL.reg);
    BYTE val = mem->readByte(addr) - 1;
    mem->writeByte(addr, val);
} */


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
 