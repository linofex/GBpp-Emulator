#include "../includes/instruction.hpp"
#include <iostream>
#include <map>
#include <vector>

instruction::instruction(std::string name, int cycles, void (*f)(Cpu*)) {
	this->name = name;
    this->cycles = cycles;
	function = f;
}


void initCBPrefix(std::map<unsigned char, instruction>& instrSetCBPrefix) {
    instrSetCBPrefix.insert(std::make_pair(0x00, instruction("RLC B", 8, rlc_B)));
    instrSetCBPrefix.insert(std::make_pair(0x01, instruction("RLC C", 8, rlc_C)));
    instrSetCBPrefix.insert(std::make_pair(0x02, instruction("RLC D", 8, rlc_D)));
    instrSetCBPrefix.insert(std::make_pair(0x03, instruction("RLC E", 8, rlc_E)));
    instrSetCBPrefix.insert(std::make_pair(0x04, instruction("RLC H", 8, rlc_H)));
    instrSetCBPrefix.insert(std::make_pair(0x05, instruction("RLC L", 8, rlc_L)));
    instrSetCBPrefix.insert(std::make_pair(0x06, instruction("RLC (HL)", 16, rlc_HL_ind)));
    instrSetCBPrefix.insert(std::make_pair(0x07, instruction("RLC A", 8, rlc_A)));
    instrSetCBPrefix.insert(std::make_pair(0x08, instruction("RRC B", 8, rrc_B)));
    instrSetCBPrefix.insert(std::make_pair(0x09, instruction("RRC C", 8, rrc_C)));
    instrSetCBPrefix.insert(std::make_pair(0x0A, instruction("RRC D", 8, rrc_D)));
    instrSetCBPrefix.insert(std::make_pair(0x0B, instruction("RRC E", 8, rrc_E)));
    instrSetCBPrefix.insert(std::make_pair(0x0C, instruction("RRC H", 8, rrc_H)));
    instrSetCBPrefix.insert(std::make_pair(0x0D, instruction("RRC L", 8, rrc_L)));
    instrSetCBPrefix.insert(std::make_pair(0x0E, instruction("RRC (HL)", 16, rrc_HL_ind)));
    instrSetCBPrefix.insert(std::make_pair(0x0F, instruction("RRC A", 8, rrc_A)));

    instrSetCBPrefix.insert(std::make_pair(0x10, instruction("RL B", 8, rl_B)));
    instrSetCBPrefix.insert(std::make_pair(0x11, instruction("RL C", 8, rl_C)));
    instrSetCBPrefix.insert(std::make_pair(0x12, instruction("RL D", 8, rl_D)));
    instrSetCBPrefix.insert(std::make_pair(0x13, instruction("RL E", 8, rl_E)));
    instrSetCBPrefix.insert(std::make_pair(0x14, instruction("RL H", 8, rl_H)));
    instrSetCBPrefix.insert(std::make_pair(0x15, instruction("RL L", 8, rl_L)));
    instrSetCBPrefix.insert(std::make_pair(0x16, instruction("RL (HL)", 16, rl_HL_ind)));
    instrSetCBPrefix.insert(std::make_pair(0x17, instruction("RL A", 8, rl_A)));
    instrSetCBPrefix.insert(std::make_pair(0x18, instruction("RR B", 8, rr_B)));
    instrSetCBPrefix.insert(std::make_pair(0x19, instruction("RR C", 8, rr_C)));
    instrSetCBPrefix.insert(std::make_pair(0x1A, instruction("RR D", 8, rr_D)));
    instrSetCBPrefix.insert(std::make_pair(0x1B, instruction("RR E", 8, rr_E)));
    instrSetCBPrefix.insert(std::make_pair(0x1C, instruction("RR H", 8, rr_H)));
    instrSetCBPrefix.insert(std::make_pair(0x1D, instruction("RR L", 8, rr_L)));
    instrSetCBPrefix.insert(std::make_pair(0x1E, instruction("RR (HL)", 16, rr_HL_ind)));
    instrSetCBPrefix.insert(std::make_pair(0x1F, instruction("RR A", 8, rr_A)));

    instrSetCBPrefix.insert(std::make_pair(0x20, instruction("SLA B", 8, sla_B)));
    instrSetCBPrefix.insert(std::make_pair(0x21, instruction("SLA C", 8, sla_C)));
    instrSetCBPrefix.insert(std::make_pair(0x22, instruction("SLA D", 8, sla_D)));
    instrSetCBPrefix.insert(std::make_pair(0x23, instruction("SLA E", 8, sla_E)));
    instrSetCBPrefix.insert(std::make_pair(0x24, instruction("SLA H", 8, sla_H)));
    instrSetCBPrefix.insert(std::make_pair(0x25, instruction("SLA L", 8, sla_L)));
    instrSetCBPrefix.insert(std::make_pair(0x26, instruction("SLA (HL)", 16, sla_HL_ind)));
    instrSetCBPrefix.insert(std::make_pair(0x27, instruction("SLA A", 8, sla_A)));
    instrSetCBPrefix.insert(std::make_pair(0x28, instruction("SRA B", 8, sra_A)));
    instrSetCBPrefix.insert(std::make_pair(0x29, instruction("SRA C", 8, sra_A)));
    instrSetCBPrefix.insert(std::make_pair(0x2A, instruction("SRA D", 8, sra_A)));
    instrSetCBPrefix.insert(std::make_pair(0x2B, instruction("SRA E", 8, sra_A)));
    instrSetCBPrefix.insert(std::make_pair(0x2C, instruction("SRA H", 8, sra_A)));
    instrSetCBPrefix.insert(std::make_pair(0x2D, instruction("SRA L", 8, sra_A)));
    instrSetCBPrefix.insert(std::make_pair(0x2E, instruction("SRA (HL)", 16, sra_A)));
    instrSetCBPrefix.insert(std::make_pair(0x2F, instruction("SRA A", 8, sra_A)));

    instrSetCBPrefix.insert(std::make_pair(0x30, instruction("SWAP B", 8,swap_B)));
    instrSetCBPrefix.insert(std::make_pair(0x31, instruction("SWAP C", 8,swap_C)));
    instrSetCBPrefix.insert(std::make_pair(0x32, instruction("SWAP D", 8,swap_D)));
    instrSetCBPrefix.insert(std::make_pair(0x33, instruction("SWAP E", 8,swap_E)));
    instrSetCBPrefix.insert(std::make_pair(0x34, instruction("SWAP H", 8,swap_H)));
    instrSetCBPrefix.insert(std::make_pair(0x35, instruction("SWAP L", 8,swap_L)));
    instrSetCBPrefix.insert(std::make_pair(0x36, instruction("SWAP (HL)", 16,swap_HL_ind)));
    instrSetCBPrefix.insert(std::make_pair(0x37, instruction("SWAP A", 8,swap_B)));
       

}

void init(std::map<unsigned char, instruction>& instrSet) {
    //std::cout<<typeid(i).name()<<std::endl;
    instrSet.insert(std::make_pair(0x80, instruction("ADD A, B", 4, add_A_B)));  
    instrSet.insert(std::make_pair(0x81, instruction("ADD A, C", 4, add_A_C)));
    instrSet.insert(std::make_pair(0x82, instruction("ADD A, D", 4, add_A_D)));
    instrSet.insert(std::make_pair(0x83, instruction("ADD A, E", 4, add_A_E)));  
    instrSet.insert(std::make_pair(0x84, instruction("ADD A, H", 4, add_A_H)));
    instrSet.insert(std::make_pair(0x85, instruction("ADD A, L", 4, add_A_L)));
    instrSet.insert(std::make_pair(0x86, instruction("ADD A, (HL)", 8, add_A_HL_ind)));  
    instrSet.insert(std::make_pair(0x87, instruction("ADD A, A", 4, add_A_A)));
    //instrSet.insert(std::make_pair(0xC6, instruction("ADD A, #", 8, add_A_n))); ->>>>>>>>>>>>>> da rivedere il parametro unsigned char

    instrSet.insert(std::make_pair(0x88, instruction("ADC A, B", 4, adc_A_B)));  
    instrSet.insert(std::make_pair(0x89, instruction("ADC A, C", 4, adc_A_C)));
    instrSet.insert(std::make_pair(0x8A, instruction("ADC A, D", 4, adc_A_D)));
    instrSet.insert(std::make_pair(0x8B, instruction("ADC A, E", 4, adc_A_E)));  
    instrSet.insert(std::make_pair(0x8C, instruction("ADC A, H", 4, adc_A_H)));
    instrSet.insert(std::make_pair(0x8D, instruction("ADC A, L", 4, adc_A_L)));
    instrSet.insert(std::make_pair(0x8E, instruction("ADC A, (HL)", 8, adc_A_HL_ind)));  
    instrSet.insert(std::make_pair(0x8F, instruction("ADC A, A", 4, adc_A_A)));  
    //instrSet.insert(std::make_pair(0xCE, instruction("ADC A, #", 8, adc_A_n))); ->>>>>>>>>>>>>> da rivedere il parametro unsigned char

    instrSet.insert(std::make_pair(0x90, instruction("SUB A, B", 4, sub_A_B)));  
    instrSet.insert(std::make_pair(0x91, instruction("SUB A, C", 4, sub_A_C)));
    instrSet.insert(std::make_pair(0x92, instruction("SUB A, D", 4, sub_A_D)));
    instrSet.insert(std::make_pair(0x93, instruction("SUB A, E", 4, sub_A_E)));  
    instrSet.insert(std::make_pair(0x94, instruction("SUB A, H", 4, sub_A_H)));
    instrSet.insert(std::make_pair(0x95, instruction("SUB A, L", 4, sub_A_L)));
    instrSet.insert(std::make_pair(0x96, instruction("SUB A, (HL)", 8, sub_A_HL_ind)));  
    instrSet.insert(std::make_pair(0x97, instruction("SUB A, A", 4, sub_A_A)));  
    //instrSet.insert(std::make_pair(0xD6, instruction("SUB A, #", 8, sub_A_n))); ->>>>>>>>>>>>>> da rivedere il parametro unsigned char

    instrSet.insert(std::make_pair(0x98, instruction("SBC A, B", 4, sbc_A_B)));  
    instrSet.insert(std::make_pair(0x99, instruction("SBC A, C", 4, sbc_A_C)));
    instrSet.insert(std::make_pair(0x9A, instruction("SBC A, D", 4, sbc_A_D)));
    instrSet.insert(std::make_pair(0x9B, instruction("SBC A, E", 4, sbc_A_E)));  
    instrSet.insert(std::make_pair(0x9C, instruction("SBC A, H", 4, sbc_A_H)));
    instrSet.insert(std::make_pair(0x9D, instruction("SBC A, L", 4, sbc_A_L)));
    instrSet.insert(std::make_pair(0x9E, instruction("SBC A, (HL)", 8, sbc_A_HL_ind)));  
    instrSet.insert(std::make_pair(0x9F, instruction("SBC A, A", 4, sbc_A_A)));  
    instrSet.insert(std::make_pair(0xDE, instruction("SBC A, #", 8, sbc_A_n)));

    instrSet.insert(std::make_pair(0xA0, instruction("AND A, B", 4, and_A_B)));  
    instrSet.insert(std::make_pair(0xA1, instruction("AND A, C", 4, and_A_C)));
    instrSet.insert(std::make_pair(0xA2, instruction("AND A, D", 4, and_A_D)));
    instrSet.insert(std::make_pair(0xA3, instruction("AND A, E", 4, and_A_E)));  
    instrSet.insert(std::make_pair(0xA4, instruction("AND A, H", 4, and_A_H)));
    instrSet.insert(std::make_pair(0xA5, instruction("AND A, L", 4, and_A_L)));
    instrSet.insert(std::make_pair(0xA6, instruction("AND A, (HL)", 8, and_A_HL_ind)));  
    instrSet.insert(std::make_pair(0xA7, instruction("AND A, A", 4, and_A_A))); 
    //--------------instrSet.insert(std::make_pair(0xE6, instruction("AND A, #", 8, and_A_n)));

    instrSet.insert(std::make_pair(0xB0, instruction("OR A, B", 4, or_A_B)));  
    instrSet.insert(std::make_pair(0xB1, instruction("OR A, C", 4, or_A_C)));
    instrSet.insert(std::make_pair(0xB2, instruction("OR A, D", 4, or_A_D)));
    instrSet.insert(std::make_pair(0xB3, instruction("OR A, E", 4, or_A_E)));  
    instrSet.insert(std::make_pair(0xB4, instruction("OR A, H", 4, or_A_H)));
    instrSet.insert(std::make_pair(0xB5, instruction("OR A, L", 4, or_A_L)));
    instrSet.insert(std::make_pair(0xB6, instruction("OR A, (HL)", 8, or_A_HL_ind)));  
    instrSet.insert(std::make_pair(0xB7, instruction("OR A, A", 4, or_A_A))); 
    //-------------------------instrSet.insert(std::make_pair(0xF6, instruction("OR A, #", 8, or_A_n)));

    instrSet.insert(std::make_pair(0xA8, instruction("XOR A, B", 4, xor_A_B)));  
    instrSet.insert(std::make_pair(0xA9, instruction("XOR A, C", 4, xor_A_C)));
    instrSet.insert(std::make_pair(0xAA, instruction("XOR A, D", 4, xor_A_D)));
    instrSet.insert(std::make_pair(0xAB, instruction("XOR A, E", 4, xor_A_E)));  
    instrSet.insert(std::make_pair(0xAC, instruction("XOR A, H", 4, xor_A_H)));
    instrSet.insert(std::make_pair(0xAD, instruction("XOR A, L", 4, xor_A_L)));
    instrSet.insert(std::make_pair(0xAE, instruction("XOR A, (HL)", 8, xor_A_HL_ind)));  
    instrSet.insert(std::make_pair(0xAF, instruction("XOR A, A", 4, xor_A_A))); 
    //-------------------instrSet.insert(std::make_pair(0xEE, instruction("XOR A, #", 8, xor_A_n)));

    instrSet.insert(std::make_pair(0xB8, instruction("CP A, B", 4, cp_A_B)));  
    instrSet.insert(std::make_pair(0xB9, instruction("CP A, C", 4, cp_A_C)));
    instrSet.insert(std::make_pair(0xBA, instruction("CP A, D", 4, cp_A_D)));
    instrSet.insert(std::make_pair(0xBB, instruction("CP A, E", 4, cp_A_E)));  
    instrSet.insert(std::make_pair(0xBC, instruction("CP A, H", 4, cp_A_H)));
    instrSet.insert(std::make_pair(0xBD, instruction("CP A, L", 4, cp_A_L)));
    instrSet.insert(std::make_pair(0xBE, instruction("CP A, (HL)", 8, cp_A_HL_ind)));  
    instrSet.insert(std::make_pair(0xBF, instruction("CP A, A", 4, cp_A_A))); 
    //----------------------instrSet.insert(std::make_pair(0xFE, instruction("CP A, #", 8, cp_A_n)));

    instrSet.insert(std::make_pair(0x04, instruction("INC B", 4, inc_B)));  
    instrSet.insert(std::make_pair(0x0C, instruction("INC C", 4, inc_C)));
    instrSet.insert(std::make_pair(0x14, instruction("INC D", 4, inc_D)));
    instrSet.insert(std::make_pair(0x1C, instruction("INC E", 4, inc_E)));  
    instrSet.insert(std::make_pair(0x24, instruction("INC H", 4, inc_H)));
    instrSet.insert(std::make_pair(0x2C, instruction("INC L", 4, inc_L)));
    instrSet.insert(std::make_pair(0x34, instruction("INC (HL)", 12, inc_HL_ind)));  
    instrSet.insert(std::make_pair(0x3C, instruction("INC A", 4, inc_A)));

    instrSet.insert(std::make_pair(0x05, instruction("DEC B", 4, dec_B)));  
    instrSet.insert(std::make_pair(0x0D, instruction("DEC C", 4, dec_C)));
    instrSet.insert(std::make_pair(0x15, instruction("DEC D", 4, dec_D)));
    instrSet.insert(std::make_pair(0x1D, instruction("DEC E", 4, dec_E)));  
    instrSet.insert(std::make_pair(0x25, instruction("DEC H", 4, dec_H)));
    instrSet.insert(std::make_pair(0x2D, instruction("DEC L", 4, dec_L)));
    instrSet.insert(std::make_pair(0x35, instruction("DEC (HL)", 12, dec_HL_ind)));  
    instrSet.insert(std::make_pair(0x3D, instruction("DEC A", 4, dec_A)));

    instrSet.insert(std::make_pair(0x09, instruction("ADD HL, BC", 8, add_HL_BC)));  
    instrSet.insert(std::make_pair(0x19, instruction("ADD HL, DE", 8, add_HL_DE)));
    instrSet.insert(std::make_pair(0x29, instruction("ADD HL, HL", 8, add_HL_HL)));
    instrSet.insert(std::make_pair(0x39, instruction("ADD HL, SP", 8, add_HL_SP)));  

    //---------------------instrSet.insert(std::make_pair(0xE8, instruction("ADD SP, N", 16, add_SP_n)));  

    instrSet.insert(std::make_pair(0x03, instruction("INC BC", 8, inc_BC)));  
    instrSet.insert(std::make_pair(0x13, instruction("INC DE", 8, inc_DE)));
    instrSet.insert(std::make_pair(0x23, instruction("INC HL", 8, inc_HL)));
    instrSet.insert(std::make_pair(0x33, instruction("INC SP", 8, inc_SP)));  
 
    instrSet.insert(std::make_pair(0x0B, instruction("DEC BC", 4, dec_BC)));
    instrSet.insert(std::make_pair(0x1B, instruction("DEC DE", 4, dec_DE)));
    instrSet.insert(std::make_pair(0x2B, instruction("DEC HL", 12, dec_HL)));  
    instrSet.insert(std::make_pair(0x3B, instruction("DEC SP", 4, dec_SP)));

    /* instrSet.insert(std::make_pair(0x06, instruction("LOAD B, n", 8, load_B_n)));
    instrSet.insert(std::make_pair(0x0E, instruction("LOAD C, n", 8, load_C_n)));
    instrSet.insert(std::make_pair(0x16, instruction("LOAD D, n", 8, load_D_n)));  
    instrSet.insert(std::make_pair(0x1E, instruction("LOAD E, n", 8, load_E_n)));
    instrSet.insert(std::make_pair(0x26, instruction("LOAD H, n", 8, load_H_n)));
    instrSet.insert(std::make_pair(0x2E, instruction("LOAD L, n", 8, load_L_n)));   */





    //std::cout<<"---------------------------------------------> "<<instrSet.at(0x80).name<<std::endl;

}

/* instruction getInstr(unsigned char opcode) {
    unsigned char temp = 0x80;
    return instrSet2[0];
} */


/* BYTE getBitIndex(BYTE r) {
    std::vector<BYTE> v = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
    return v.at(r);
} */

//----------------------- EMPTY -------------------------------------
static void not_defined() {
    std::cout<<"Instruction not defined"<<std::endl;
}

//-----------------------ADD-------------------------------------
static void add(Cpu* c, unsigned char n) {
   std::cout<<"inizio add"<<std::endl;

   unsigned short res = c->getA() + n;
    
    if(res == 0)        //sum = 0
        c->setFlag(flagZ);
    else
        c->resetFlag(flagZ);

    c->setA(res);

    c->resetFlag(flagN);
        
    if(res > 0x00FF)  //sum overflow
        c->setFlag(flagC);
    else
        c->resetFlag(flagC);
        
    if(((n & 0x0F) + (c->getA() & 0x0F)) > 0x0F)    //if carry from bit 3
        c->setFlag(flagH);
    else
        c->resetFlag(flagH);

    std::cout<<"fine add"<<std::endl;
    
}

static void add_A_B(Cpu* c) {add(c, c->getB());}
static void add_A_C(Cpu* c) {add(c, c->getC());}
static void add_A_D(Cpu* c) {add(c, c->getD());}
static void add_A_E(Cpu* c) {add(c, c->getE());}
static void add_A_H(Cpu* c) {add(c, c->getH());}
static void add_A_L(Cpu* c) {add(c, c->getL());}
static void add_A_A(Cpu* c) {add(c, c->getA());}
static void add_A_n(Cpu* c) {
    unsigned char data = c->readByte(c->getPC());
    c->incPC();
    add(c, data);
    }
static void add_A_HL_ind(Cpu* c) {
    WORD addr = c->getHL();
    unsigned char n = c->readByte(addr);
    add(c, n);
}

static void adc(Cpu* c, unsigned char n) {
    unsigned char carry = c->isFlagCarry();  //carry = 1 or 0
    add(c, n + carry);
}
static void adc_A_B(Cpu* c) {adc(c, c->getB());}
static void adc_A_C(Cpu* c) {adc(c, c->getC());}
static void adc_A_D(Cpu* c) {adc(c, c->getD());}
static void adc_A_E(Cpu* c) {adc(c, c->getE());}
static void adc_A_H(Cpu* c) {adc(c, c->getH());}
static void adc_A_L(Cpu* c) {adc(c, c->getL());}
static void adc_A_A(Cpu* c) {adc(c, c->getA());}
static void adc_A_n(Cpu* c) {
    unsigned char data = c->readByte(c->getPC());
    c->incPC();
    adc(c, data);
    }
static void adc_A_HL_ind(Cpu* c) {
    WORD addr = c->getHL();
    unsigned char n = c->readByte(addr);
    adc(c, n);
}

static void sub(Cpu* c, unsigned char n) {
    signed short res = c->getA() - n;

    if(res == 0)        //sub = 0
        c->setFlag(flagZ);
    else
        c->resetFlag(flagZ);

    c->setA(res);
    
    c->setFlag(flagN);
        
    if(res < 0)  //sub with borrow
        c->setFlag(flagC);
    else
        c->resetFlag(flagC);
        
    if(((c->getA() & 0x0F) - (n & 0x0F)) < 0)    //if borrow from bit 3
        c->setFlag(flagH);
    else
        c->resetFlag(flagH);
}
static void sub_A_B(Cpu* c) {sub(c, c->getB());}
static void sub_A_C(Cpu* c) {sub(c, c->getC());}
static void sub_A_D(Cpu* c) {sub(c, c->getD());}
static void sub_A_E(Cpu* c) {sub(c, c->getE());}
static void sub_A_H(Cpu* c) {sub(c, c->getH());}
static void sub_A_L(Cpu* c) {sub(c, c->getL());}
static void sub_A_A(Cpu* c) {sub(c, c->getA());}
static void sub_A_n(Cpu* c) {
    unsigned char data = c->readByte(c->getPC());
    c->incPC();
    sub(c, data);
}
static void sub_A_HL_ind(Cpu* c) {
    WORD addr = c->getHL();
    unsigned char n = c->readByte(addr);
    sub(c, n);
}

static void sbc(Cpu* c, unsigned char n) {
    unsigned char carry = c->isFlagCarry() ? 1 : 0;  //carry = 1 or 0
    sub(c, n + carry);
}
static void sbc_A_B(Cpu* c) {sbc(c, c->getB());}
static void sbc_A_C(Cpu* c) {sbc(c, c->getC());}
static void sbc_A_D(Cpu* c) {sbc(c, c->getD());}
static void sbc_A_E(Cpu* c) {sbc(c, c->getE());}
static void sbc_A_H(Cpu* c) {sbc(c, c->getH());}
static void sbc_A_L(Cpu* c) {sbc(c, c->getL());}
static void sbc_A_A(Cpu* c) {sbc(c, c->getA());}
static void sbc_A_n(Cpu* c) {
    unsigned char data = c->readByte(c->getPC());
    c->incPC();
    sbc(c, data);
}
static void sbc_A_HL_ind(Cpu* c) {
    WORD addr = c->getHL();
    unsigned char n = c->readByte(addr);
    sbc(c, n);
}

static void and_(Cpu* c, unsigned char n) {
    unsigned char res = c->getA() & n;

    if(res == 0)        //and = 0
        c->setFlag(flagZ);
    else
        c->resetFlag(flagZ);

    c->setA(res);
    
    c->setFlag(flagH);
    c->resetFlag(flagC);
    c->resetFlag(flagN);    
}
static void and_A_B(Cpu* c) {and_(c, c->getB());}
static void and_A_C(Cpu* c) {and_(c, c->getC());}
static void and_A_D(Cpu* c) {and_(c, c->getD());}
static void and_A_E(Cpu* c) {and_(c, c->getE());}
static void and_A_H(Cpu* c) {and_(c, c->getH());}
static void and_A_L(Cpu* c) {and_(c, c->getL());}
static void and_A_A(Cpu* c) {and_(c, c->getA());}
static void and_A_n(Cpu* c) {
    unsigned char data = c->readByte(c->getPC());
    c->incPC();
    and_(c, data);
}
static void and_A_HL_ind(Cpu* c) {
    WORD addr = c->getHL();
    unsigned char n = c->readByte(addr);
    and_(c, n);
}

static void or_(Cpu* c, unsigned char n) {
    unsigned char res = c->getA() | n;

    if(res == 0)        //or = 0
        c->setFlag(flagZ);
    else
        c->resetFlag(flagZ);

    c->setA(res);
    
    c->resetFlag(flagH);
    c->resetFlag(flagC);
    c->resetFlag(flagN);
}
static void or_A_B(Cpu* c) {or_(c, c->getB());}
static void or_A_C(Cpu* c) {or_(c, c->getC());}
static void or_A_D(Cpu* c) {or_(c, c->getD());}
static void or_A_E(Cpu* c) {or_(c, c->getE());}
static void or_A_H(Cpu* c) {or_(c, c->getH());}
static void or_A_L(Cpu* c) {or_(c, c->getL());}
static void or_A_A(Cpu* c) {or_(c, c->getA());}
static void or_A_n(Cpu* c) {
    unsigned char data = c->readByte(c->getPC());
    c->incPC();
    or_(c, data);
}
static void or_A_HL_ind(Cpu* c) {
    WORD addr = c->getHL();
    unsigned char n = c->readByte(addr);
    or_(c, n);
}

static void xor_(Cpu* c, unsigned char n) {
    unsigned char res = c->getA() ^ n;

    if(res == 0)        //xor = 0
        c->setFlag(flagZ);
    else
        c->resetFlag(flagZ);

    c->setA(res);
    
    c->resetFlag(flagH);
    c->resetFlag(flagC);
    c->resetFlag(flagN);        
}
static void xor_A_B(Cpu* c) {xor_(c, c->getB());}
static void xor_A_C(Cpu* c) {xor_(c, c->getC());}
static void xor_A_D(Cpu* c) {xor_(c, c->getD());}
static void xor_A_E(Cpu* c) {xor_(c, c->getE());}
static void xor_A_H(Cpu* c) {xor_(c, c->getH());}
static void xor_A_L(Cpu* c) {xor_(c, c->getL());}
static void xor_A_A(Cpu* c) {xor_(c, c->getA());}
static void xor_A_n(Cpu* c) {
    unsigned char data = c->readByte(c->getPC());
    c->incPC();
    xor_(c, data);
}
static void xor_A_HL_ind(Cpu* c) {
    WORD addr = c->getHL();
    unsigned char n = c->readByte(addr);
    xor_(c, n);
}

static void cp(Cpu* c, unsigned char n) {
    signed short res = c->getA() - n;

    if(res == 0)        //sub = 0
        c->setFlag(flagZ);
    else
        c->resetFlag(flagZ);
    
    c->setFlag(flagN);
        
    if(res < 0)  //sub with borrow
        c->setFlag(flagC);
    else
        c->resetFlag(flagC);
        
    if(((c->getA() & 0x0F) - (n & 0x0F)) < 0)    //if borrow from bit 3
        c->setFlag(flagH);
    else
        c->resetFlag(flagH);
}
static void cp_A_B(Cpu* c) {cp(c, c->getB());}
static void cp_A_C(Cpu* c) {cp(c, c->getC());}
static void cp_A_D(Cpu* c) {cp(c, c->getD());}
static void cp_A_E(Cpu* c) {cp(c, c->getE());}
static void cp_A_H(Cpu* c) {cp(c, c->getH());}
static void cp_A_L(Cpu* c) {cp(c, c->getL());}
static void cp_A_A(Cpu* c) {cp(c, c->getA());}
static void cp_A_n(Cpu* c, unsigned char n) {
    unsigned char data = c->readByte(c->getPC());
    c->incPC();
    cp(c, data);
}
static void cp_A_HL_ind(Cpu* c) {
    WORD addr = c->getHL();
    unsigned char n = c->readByte(addr);
    cp(c, n);
}

static BYTE inc(Cpu* c, unsigned char n) {
    unsigned short res = n + 1;

    if(res == 0)        //res = 0
        c->setFlag(flagZ);
    else
        c->resetFlag(flagZ);
    
    c->resetFlag(flagN);
        
    if((res & 0x0F) > 0x0F)    //if carry from bit 3
        c->setFlag(flagH);
    else
        c->resetFlag(flagH);

    return (unsigned char) res;
}
static void inc_A(Cpu* c) {c->setA(inc(c, c->getA()));}
static void inc_B(Cpu* c) {c->setA(inc(c, c->getB()));}
static void inc_C(Cpu* c) {c->setA(inc(c, c->getC()));}
static void inc_D(Cpu* c) {c->setA(inc(c, c->getD()));}
static void inc_E(Cpu* c) {c->setA(inc(c, c->getE()));}
static void inc_H(Cpu* c) {c->setA(inc(c, c->getH()));}
static void inc_L(Cpu* c) {c->setA(inc(c, c->getL()));}
static void inc_HL_ind(Cpu* c) {
    WORD addr = c->getHL();
    unsigned char n = c->readByte(addr);
    c->setA(inc(c, n));
}

static BYTE dec(Cpu* c, unsigned char n) {
    unsigned short res = n - 1;

    if(res == 0)        //res = 0
        c->setFlag(flagZ);
    else
        c->resetFlag(flagZ);
    
    c->setFlag(flagN);
        
    if((res & 0x0F) < 0)    //if borrow from bit 3
        c->setFlag(flagH);
    else
        c->resetFlag(flagH);

    return (unsigned char) res;
}
static void dec_A(Cpu* c) {c->setA(dec(c, c->getA()));}
static void dec_B(Cpu* c) {c->setA(dec(c, c->getB()));}
static void dec_C(Cpu* c) {c->setA(dec(c, c->getC()));}
static void dec_D(Cpu* c) {c->setA(dec(c, c->getD()));}
static void dec_E(Cpu* c) {c->setA(dec(c, c->getE()));}
static void dec_H(Cpu* c) {c->setA(dec(c, c->getH()));}
static void dec_L(Cpu* c) {c->setA(dec(c, c->getL()));}
static void dec_HL_ind(Cpu* c) {
    WORD addr = c->getHL();
    unsigned char n = c->readByte(addr);
    c->setA(dec(c, n));
}

static void add_HL(Cpu* c, WORD val) {
    
    unsigned long res = c->getHL() + val;

    c->setHL((unsigned short) res);
 
    c->resetFlag(flagN);

    if(res & 0xFFFF0000)
        c->setFlag(flagC);
    else
        c->resetFlag(flagC);
    
    if(((c->getHL() & 0x0FFF) + (val & 0x0FFF)) > 0x0FFF)
        c->setFlag(flagH);
	else
        c->resetFlag(flagH);
}
static void add_HL_BC(Cpu* c) {add_HL(c, c->getBC());};
static void add_HL_DE(Cpu* c) {add_HL(c, c->getDE());};
static void add_HL_HL(Cpu* c) {add_HL(c, c->getHL());};
static void add_HL_SP(Cpu* c) {add_HL(c, c->getSP());};

static void add_SP_n(Cpu* c) {

    unsigned char n = c->readByte(c->getPC());
    c->incPC();

    c->resetFlag(flagZ);
    c->resetFlag(flagN);

    unsigned long res = c->getSP() + n;

    c->setSP((unsigned short) res);
 
    c->resetFlag(flagN);

    if(res & 0xFFFF0000)
        c->setFlag(flagC);
    else
        c->resetFlag(flagC);
    
    if(((c->getSP() & 0x0F) + (n & 0x0F)) > 0x0F)
        c->setFlag(flagH);
	else
        c->resetFlag(flagH);

};

static void inc_HL(Cpu* c) {c->setHL(c->getHL() + 1);};
static void inc_SP(Cpu* c) {c->incSP();};
static void inc_DE(Cpu* c) {c->setDE(c->getDE() + 1);};
static void inc_BC(Cpu* c) {c->setBC(c->getBC() + 1);};

static void dec_HL(Cpu* c) {c->setHL(c->getHL() - 1);};
static void dec_SP(Cpu* c) {c->decSP();};
static void dec_DE(Cpu* c) {c->setDE(c->getDE() - 1);};
static void dec_BC(Cpu* c) {c->setBC(c->getBC() - 1);};

static BYTE load_nn_n(Cpu* c) {
    BYTE n = c->readByte(c->getPC());
    c->incPC();
    return n;
}
static void load_A_n(Cpu* c) {c->setA(load_nn_n(c));}
static void load_B_n(Cpu* c) {c->setB(load_nn_n(c));}
static void load_C_n(Cpu* c) {c->setC(load_nn_n(c));}
static void load_D_n(Cpu* c) {c->setD(load_nn_n(c));}
static void load_E_n(Cpu* c) {c->setE(load_nn_n(c));}
static void load_H_n(Cpu* c) {c->setH(load_nn_n(c));}
static void load_L_n(Cpu* c) {c->setL(load_nn_n(c));}

static void load_A_A(Cpu* c) {c->setA(c->getA());}
static void load_A_B(Cpu* c) {c->setA(c->getB());}
static void load_A_C(Cpu* c) {c->setA(c->getC());}
static void load_A_D(Cpu* c) {c->setA(c->getD());}
static void load_A_E(Cpu* c) {c->setA(c->getE());}
static void load_A_H(Cpu* c) {c->setA(c->getH());}
static void load_A_L(Cpu* c) {c->setA(c->getL());}
static void load_A_HL_ind(Cpu* c) {
    WORD addr = c->getHL();
    unsigned char n = c->readByte(addr);
    c->setA(n);
}

static void load_B_A(Cpu* c) {c->setB(c->getA());}
static void load_B_B(Cpu* c) {c->setB(c->getB());}
static void load_B_C(Cpu* c) {c->setB(c->getC());}
static void load_B_D(Cpu* c) {c->setB(c->getD());}
static void load_B_E(Cpu* c) {c->setB(c->getE());}
static void load_B_H(Cpu* c) {c->setB(c->getH());}
static void load_B_L(Cpu* c) {c->setB(c->getL());}
static void load_B_HL_ind(Cpu* c) {
    WORD addr = c->getHL();
    unsigned char n = c->readByte(addr);
    c->setB(n);
}

static void load_C_A(Cpu* c) {c->setC(c->getA());}
static void load_C_B(Cpu* c) {c->setC(c->getB());}
static void load_C_C(Cpu* c) {c->setC(c->getC());}
static void load_C_D(Cpu* c) {c->setC(c->getD());}
static void load_C_E(Cpu* c) {c->setC(c->getE());}
static void load_C_H(Cpu* c) {c->setC(c->getH());}
static void load_C_L(Cpu* c) {c->setC(c->getL());}
static void load_C_HL_ind(Cpu* c) {
    WORD addr = c->getHL();
    unsigned char n = c->readByte(addr);
    c->setC(n);
}

static void load_D_A(Cpu* c) {c->setD(c->getA());}
static void load_D_B(Cpu* c) {c->setD(c->getB());}
static void load_D_C(Cpu* c) {c->setD(c->getC());}
static void load_D_D(Cpu* c) {c->setD(c->getD());}
static void load_D_E(Cpu* c) {c->setD(c->getE());}
static void load_D_H(Cpu* c) {c->setD(c->getH());}
static void load_D_L(Cpu* c) {c->setD(c->getL());}
static void load_D_HL_ind(Cpu* c) {
    WORD addr = c->getHL();
    unsigned char n = c->readByte(addr);
    c->setD(n);
}

static void load_E_A(Cpu* c) {c->setE(c->getA());}
static void load_E_B(Cpu* c) {c->setE(c->getB());}
static void load_E_C(Cpu* c) {c->setE(c->getC());}
static void load_E_D(Cpu* c) {c->setE(c->getD());}
static void load_E_E(Cpu* c) {c->setE(c->getE());}
static void load_E_H(Cpu* c) {c->setE(c->getH());}
static void load_E_L(Cpu* c) {c->setE(c->getL());}
static void load_E_HL_ind(Cpu* c) {
    WORD addr = c->getHL();
    unsigned char n = c->readByte(addr);
    c->setE(n);
}

static void load_H_A(Cpu* c) {c->setH(c->getA());}
static void load_H_B(Cpu* c) {c->setH(c->getB());}
static void load_H_C(Cpu* c) {c->setH(c->getC());}
static void load_H_D(Cpu* c) {c->setH(c->getD());}
static void load_H_E(Cpu* c) {c->setH(c->getE());}
static void load_H_H(Cpu* c) {c->setH(c->getH());}
static void load_H_L(Cpu* c) {c->setH(c->getL());}
static void load_H_HL_ind(Cpu* c) {
    WORD addr = c->getHL();
    unsigned char n = c->readByte(addr);
    c->setH(n);
}

static void load_L_A(Cpu* c) {c->setL(c->getA());}
static void load_L_B(Cpu* c) {c->setL(c->getB());}
static void load_L_C(Cpu* c) {c->setL(c->getC());}
static void load_L_D(Cpu* c) {c->setL(c->getD());}
static void load_L_E(Cpu* c) {c->setL(c->getE());}
static void load_L_H(Cpu* c) {c->setL(c->getH());}
static void load_L_L(Cpu* c) {c->setL(c->getL());}
static void load_L_HL_ind(Cpu* c) {
    WORD addr = c->getHL();
    unsigned char n = c->readByte(addr);
    c->setL(n);
}

static void load_HL_ind_x(Cpu* c, unsigned char n) {
    WORD addr = c->getHL();
    c->writeByte(addr, n);
}
static void load_HL_ind_A(Cpu* c) {load_HL_ind_x(c, c->getA());}
static void load_HL_ind_B(Cpu* c) {load_HL_ind_x(c, c->getB());}
static void load_HL_ind_C(Cpu* c) {load_HL_ind_x(c, c->getC());}
static void load_HL_ind_D(Cpu* c) {load_HL_ind_x(c, c->getD());}
static void load_HL_ind_E(Cpu* c) {load_HL_ind_x(c, c->getE());}
static void load_HL_ind_H(Cpu* c) {load_HL_ind_x(c, c->getH());}
static void load_HL_ind_L(Cpu* c) {load_HL_ind_x(c, c->getL());}
static void load_HL_ind_n(Cpu* c) {
    BYTE n = c->readByte(c->getPC());
    load_HL_ind_x(c, n);
}


static void load_A_x_ind(Cpu* c, unsigned short  n) {
    unsigned char res = c->readByte(n);
    c->setA(res);
}
static void load_A_BC_ind(Cpu* c) {load_A_x_ind(c, c->getBC());}
static void load_A_DE_ind(Cpu* c) {load_A_x_ind(c, c->getDE());}
//static void load_A_HL_ind(Cpu* c) {load_A_x_ind(c, c->getHL());}
static void load_A_nn_ind(Cpu* c) {
    WORD nn = c->readWord(c->getPC());
    c->incPC();
    c->incPC();    
    load_A_x_ind(c, nn);
}


static void load_A_n(Cpu* c, unsigned char n) {c->setA(n);}

//static void load_A_HL_ind(Cpu* c) {load_A_x_ind(c, c->getHL());}

/* static void load_B_A(Cpu* c) {c->setB(c->getA());}
static void load_C_A(Cpu* c) {c->setC(c->getA());}
static void load_D_A(Cpu* c) {c->setD(c->getA());}
static void load_E_A(Cpu* c) {c->setE(c->getA());}
static void load_H_A(Cpu* c) {c->setH(c->getA());}
static void load_L_A(Cpu* c) {c->setL(c->getA());} */

static void load_xx_ind_A(Cpu* c, unsigned short addr) {
    c->writeByte(addr, c->getA());
}
static void load_BC_ind_A(Cpu* c) {load_xx_ind_A(c, c->getBC());}
static void load_DE_ind_A(Cpu* c) {load_xx_ind_A(c, c->getDE());}
//static void load_HL_ind_A(Cpu* c) {load_xx_ind_A(c, c->getHL());}
static void load_nn_ind_A(Cpu* c) {
    WORD nn = c->readWord(c->getPC());
    c->incPC();
    c->incPC();
    load_xx_ind_A(c, nn);
}

static void load_A_C_ind(Cpu* c) {
    WORD res = c->readByte( 0xFF00 + c->getC());
    c->setA(res);
}

static void load_C_ind_A(Cpu* c) {
    WORD addr = c->getC() + 0xFF00;
    c->writeByte(addr, c->getA());
}

/* static void load_A_HLD_ind(Cpu* c) {
    loadd_A_HL_ind(c);
}
static void load_A_HL__ind(Cpu* c) {
    loadd_A_HL_ind(c);
} */
static void loadd_A_HL_ind(Cpu* c) {
    load_A_HL_ind(c);
    dec_HL(c);
}

/* static void load_HLD_ind_A(Cpu* c) {
    loadd_HL_ind_A(c);
}
static void loadHL__ind_A(Cpu* c) {
    loadd_HL_ind_A(c);
} */
static void loadd_HL_ind_A(Cpu* c) {
    load_HL_ind_A(c);
    dec_HL(c);
}

static void loadi_A_HL_ind(Cpu* c) {
    load_A_HL_ind(c);
    inc_HL(c);
}

static void loadi_HL_ind_A(Cpu* c) {
    load_HL_ind_A(c);
    inc_HL(c);
}

static void loadh_n_ind_A(Cpu* c) {
    BYTE n = c->readByte(c->getPC());
    c->incPC();
    c->writeByte(0xFF00 + n, c->getA());
}

static void loadh_A_n_ind(Cpu* c) {
    BYTE n = c->readByte(c->getPC());
    c->incPC();
    c->setA(0xFF00 + n);
}

static BYTE load_n_nn(Cpu* c) {
    WORD nn = c->readWord(c->getPC());
    c->incPC();
    c->incPC();
    return nn;
}
static void load_BC_nn(Cpu* c) {c->setBC(load_n_nn(c));}
static void load_DE_nn(Cpu* c) {c->setDE(load_n_nn(c));}
static void load_HL_nn(Cpu* c) {c->setHL(load_n_nn(c));}
static void load_SP_nn(Cpu* c) {c->setSP(load_n_nn(c));}

static void load_SP_HL(Cpu* c) {
    c->setSP(c->getHL());
}
static void loadhl_SP_n(Cpu* c) {
    BYTE n = c->readByte(c->getPC());
    c->incPC();

    int res = c->getSP() + n;
    c->resetFlag(flagZ);
    c->resetFlag(flagN);

    if(((c->getSP() & 0x0F) + (n & 0x0F)) > 0x0F)
        c->setFlag(flagH);
    else
        c->resetFlag(flagH);
    
    if(res > 0x0000FFFF)
        c->setFlag(flagC);
    else
        c->resetFlag(flagC);

    c->setHL((unsigned short)res);
}
static void load_nn_SP(Cpu* c) {
    WORD nn = c->readWord(c->getPC());
    c->incPC();
    c->incPC();

    c->writeWord(nn, c->getSP());
}
static void push_nn(Cpu* c, unsigned short nn) {
    c->writeWord(c->getSP(), nn);
    c->decSP();
    c->decSP();
}
static void push_AF(Cpu* c) {
    push_nn(c, c->getAF());
}
static void push_BC(Cpu* c) {
    push_nn(c, c->getBC());
}
static void push_DE(Cpu* c) {
    push_nn(c, c->getDE());
}
static void push_HL(Cpu* c) {
    push_nn(c, c->getHL());
}

static WORD pop_nn(Cpu* c) {
    WORD nn = c->readWord(c->getSP());
    c->incSP();
    c->incSP();
    return nn;
}
static void pop_AF(Cpu* c) {c->setAF(pop_nn(c));}
static void pop_BC(Cpu* c) {c->setBC(pop_nn(c));}
static void pop_DE(Cpu* c) {c->setDE(pop_nn(c));}
static void pop_HL(Cpu* c) {c->setHL(pop_nn(c));}


BYTE swap_n(Cpu* c, unsigned char n) {
    c->resetFlag(flagN);
    c->resetFlag(flagH);
    c->resetFlag(flagC);

    BYTE high = n & 0xF0;
    high >>= 4;
    BYTE low = n & 0x0F;
    low <<= 4;
    if((high + low) == 0)
        c->setFlag(flagZ);
    else
        c->resetFlag(flagZ);
    return high + low;
}

static void swap_A(Cpu* c) {c->setA(swap_n(c, c->getA()));}
static void swap_B(Cpu* c) {c->setA(swap_n(c, c->getB()));}
static void swap_C(Cpu* c) {c->setA(swap_n(c, c->getC()));}
static void swap_D(Cpu* c) {c->setA(swap_n(c, c->getD()));}
static void swap_E(Cpu* c) {c->setA(swap_n(c, c->getE()));}
static void swap_H(Cpu* c) {c->setA(swap_n(c, c->getH()));}
static void swap_L(Cpu* c) {c->setA(swap_n(c, c->getL()));}
static void swap_HL_ind(Cpu* c) {
    WORD addr = c->getHL();
    unsigned char n = c->readByte(addr);
    c->setHL(swap_n(c, c->getHL()));    
}

static void daa(Cpu* c) {
    unsigned char a_h = (c->getA() & 0xF0) >> 4;
    unsigned char a_l = c->getA() & 0x0F;

    c->resetFlag(flagH);
    unsigned short res = (a_h * 10) + a_l;
    
    if(res == 0)
        c->setFlag(flagZ);
    else
        c->resetFlag(flagZ);
    
    if(res > 256)
        c->setFlag(flagC);
    else
        c->resetFlag(flagC);
    
    c->setA(res);
}

static void cpl(Cpu* c) {
    c->setFlag(flagN);
    c->setFlag(flagH);

    c->setA(~(c->getA()));
}
static void ccf(Cpu* c) {
    unsigned char carry = c->isFlagCarry();
    if(carry == 0)
        c->setFlag(flagC);
    else
        c->resetFlag(flagC);

    c->resetFlag(flagH);
    c->resetFlag(flagN);
}
static void scf(Cpu* c) {
    c->setFlag(flagC);
    c->resetFlag(flagH);
    c->resetFlag(flagN);
}
static void nop(Cpu* c) {}
static void halt(Cpu* c) {
    c->setPC(c->getPC() - 1);
}
static void stop() {}
static void di(Cpu* c) {
    c->resetIntMasterEnable();
}
static void ei(Cpu* c) {
    c->setIntMasterEnable();
}

static BYTE rlc(Cpu* c, unsigned char a) {
    c->resetFlag(flagN);
    c->resetFlag(flagH);

    BYTE carry = ((a & 0x80) >> 7);
    (carry == 1) ? c->setFlag(flagC) : c->resetFlag(flagC);

    a <<= 1;
    a += carry;
    if(a == 0)
        c->setFlag(flagZ);
    else
        c->resetFlag(flagZ);
    
    return a;
}
static void rlc_A(Cpu* c) {c->setA(rlc(c, c->getA()));}
static void rlc_B(Cpu* c) {c->setB(rlc(c, c->getB()));}
static void rlc_C(Cpu* c) {c->setC(rlc(c, c->getC()));}
static void rlc_D(Cpu* c) {c->setD(rlc(c, c->getD()));}
static void rlc_E(Cpu* c) {c->setE(rlc(c, c->getE()));}
static void rlc_H(Cpu* c) {c->setH(rlc(c, c->getH()));}
static void rlc_L(Cpu* c) {c->setL(rlc(c, c->getL()));}
static void rlc_HL_ind(Cpu* c) {
    BYTE addr = c->getHL();
    BYTE res = rlc(c, c->readByte(addr));
    c->writeByte(addr, res);
}

static BYTE rl(Cpu* c, unsigned char a) {
    c->resetFlag(flagN);
    c->resetFlag(flagH);

    BYTE a_7 = ((a & 0x80) >> 7);
    a <<= 1;
    unsigned char carry = c->isFlagCarry();
    a+= carry;
    
    if(a_7 == 1)
        c->setFlag(flagC);
    else
        c->resetFlag(flagC);

    if(a == 0)
        c->setFlag(flagZ);
    else
        c->resetFlag(flagZ);
    
    return a;
}
static void rl_A(Cpu* c) {c->setA(rl(c, c->getA()));}
static void rl_B(Cpu* c) {c->setB(rl(c, c->getB()));}
static void rl_C(Cpu* c) {c->setC(rl(c, c->getC()));}
static void rl_D(Cpu* c) {c->setD(rl(c, c->getD()));}
static void rl_E(Cpu* c) {c->setE(rl(c, c->getE()));}
static void rl_H(Cpu* c) {c->setH(rl(c, c->getH()));}
static void rl_L(Cpu* c) {c->setL(rl(c, c->getL()));}
static void rl_HL_ind(Cpu* c) {
    BYTE addr = c->getHL();
    BYTE res = rl(c, c->readByte(addr));
    c->writeByte(addr, res);
}

static BYTE rrc(Cpu* c, unsigned char a) {
    c->resetFlag(flagN);
    c->resetFlag(flagH);

    BYTE carry = (a & 0x01);
    (carry == 1) ? c->setFlag(flagC) : c->resetFlag(flagC);

    a >>= 1;
    a += (carry << 7);
    if(a == 0)
        c->setFlag(flagZ);
    else
        c->resetFlag(flagZ);
    
    return a;
}
static void rrc_A(Cpu* c) {c->setA(rrc(c, c->getA()));}
static void rrc_B(Cpu* c) {c->setB(rrc(c, c->getB()));}
static void rrc_C(Cpu* c) {c->setC(rrc(c, c->getC()));}
static void rrc_D(Cpu* c) {c->setD(rrc(c, c->getD()));}
static void rrc_E(Cpu* c) {c->setE(rrc(c, c->getE()));}
static void rrc_H(Cpu* c) {c->setH(rrc(c, c->getH()));}
static void rrc_L(Cpu* c) {c->setL(rrc(c, c->getL()));}
static void rrc_HL_ind(Cpu* c) {
    BYTE addr = c->getHL();
    BYTE res = rrc(c, c->readByte(addr));
    c->writeByte(addr, res);
}

static BYTE rr(Cpu* c, unsigned char a) {
    c->resetFlag(flagN);
    c->resetFlag(flagH);

    BYTE a_0 = (a & 0x01);
    a >>= 1;
    unsigned char carry = c->isFlagCarry();
    a+= (carry << 7);
    
    if(a_0 == 1)
        c->setFlag(flagC);
    else
        c->resetFlag(flagC);

    if(a == 0)
        c->setFlag(flagZ);
    else
        c->resetFlag(flagZ);
    
    return a;
}
static void rr_A(Cpu* c) {c->setA(rr(c, c->getA()));}
static void rr_B(Cpu* c) {c->setB(rr(c, c->getB()));}
static void rr_C(Cpu* c) {c->setC(rr(c, c->getC()));}
static void rr_D(Cpu* c) {c->setD(rr(c, c->getD()));}
static void rr_E(Cpu* c) {c->setE(rr(c, c->getE()));}
static void rr_H(Cpu* c) {c->setH(rr(c, c->getH()));}
static void rr_L(Cpu* c) {c->setL(rr(c, c->getL()));}
static void rr_HL_ind(Cpu* c) {
    BYTE addr = c->getHL();
    BYTE res = rr(c, c->readByte(addr));
    c->writeByte(addr, res);
}

static BYTE sla(Cpu* c, unsigned char a) {
    c->resetFlag(flagN);
    c->resetFlag(flagH);

    BYTE a_7 = ((a & 0x80) >> 7);
    a <<= 1;
    
    if(a_7 == 1)
        c->setFlag(flagC);
    else
        c->resetFlag(flagC);

    if(a == 0)
        c->setFlag(flagZ);
    else
        c->resetFlag(flagZ);
    
    return a;
}
static void sla_A(Cpu* c) {c->setA(sla(c, c->getA()));}
static void sla_B(Cpu* c) {c->setB(sla(c, c->getB()));}
static void sla_C(Cpu* c) {c->setC(sla(c, c->getC()));}
static void sla_D(Cpu* c) {c->setD(sla(c, c->getD()));}
static void sla_E(Cpu* c) {c->setE(sla(c, c->getE()));}
static void sla_H(Cpu* c) {c->setH(sla(c, c->getH()));}
static void sla_L(Cpu* c) {c->setL(sla(c, c->getL()));}
static void sla_HL_ind(Cpu* c) {
    BYTE addr = c->getHL();
    BYTE res = sla(c, c->readByte(addr));
    c->writeByte(addr, res);
}

static BYTE sra(Cpu* c, unsigned char a) {
    c->resetFlag(flagN);
    c->resetFlag(flagH);

    BYTE a_7 = (a & 0x80);
    BYTE a_0 = (a & 0x01);
    a >>= 1;

    if(a_0 == 1)
        c->setFlag(flagC);
    else
        c->resetFlag(flagC);

    a |= a_7;

    if(a == 0)
        c->setFlag(flagZ);
    else
        c->resetFlag(flagZ);
    
    return a;
}
static void sra_A(Cpu* c) {c->setA(sra(c, c->getA()));}
static void sra_B(Cpu* c) {c->setB(sra(c, c->getB()));}
static void sra_C(Cpu* c) {c->setC(sra(c, c->getC()));}
static void sra_D(Cpu* c) {c->setD(sra(c, c->getD()));}
static void sra_E(Cpu* c) {c->setE(sra(c, c->getE()));}
static void sra_H(Cpu* c) {c->setH(sra(c, c->getH()));}
static void sra_L(Cpu* c) {c->setL(sra(c, c->getL()));}
static void sra_HL_ind(Cpu* c) {
    BYTE addr = c->getHL();
    BYTE res = sra(c, c->readByte(addr));
    c->writeByte(addr, res);
}

static BYTE srl(Cpu* c, unsigned char a) {
    c->resetFlag(flagN);
    c->resetFlag(flagH);

    BYTE a_0 = (a & 0x01);
    a >>= 1;

    if(a_0 == 1)
        c->setFlag(flagC);
    else
        c->resetFlag(flagC);

    if(a == 0)
        c->setFlag(flagZ);
    else
        c->resetFlag(flagZ);
    
    return a;
}
static void srl_A(Cpu* c) {c->setA(srl(c, c->getA()));}
static void srl_B(Cpu* c) {c->setB(srl(c, c->getB()));}
static void srl_C(Cpu* c) {c->setC(srl(c, c->getC()));}
static void srl_D(Cpu* c) {c->setD(srl(c, c->getD()));}
static void srl_E(Cpu* c) {c->setE(srl(c, c->getE()));}
static void srl_H(Cpu* c) {c->setH(srl(c, c->getH()));}
static void srl_L(Cpu* c) {c->setL(srl(c, c->getL()));}
static void srl_HL_ind(Cpu* c) {
    BYTE addr = c->getHL();
    BYTE res = srl(c, c->readByte(addr));
    c->writeByte(addr, res);
}

static void bit_b_r(Cpu* c, unsigned char r, unsigned char b) {
    c->resetFlag(flagN);
    c->setFlag(flagH);

    //BYTE b = c->readByte(c->getPC());
    c->incPC();

    b = (b >> r) & 0x01;
    if(!b)
        c->setFlag(flagZ);
    else
        c->resetFlag(flagZ);
}
static void bit_A_0(Cpu* c) {bit_b_r(c, c->getA(), 0);}
static void bit_A_1(Cpu* c) {bit_b_r(c, c->getA(), 1);}
static void bit_A_2(Cpu* c) {bit_b_r(c, c->getA(), 2);}
static void bit_A_3(Cpu* c) {bit_b_r(c, c->getA(), 3);}
static void bit_A_4(Cpu* c) {bit_b_r(c, c->getA(), 4);}
static void bit_A_5(Cpu* c) {bit_b_r(c, c->getA(), 5);}
static void bit_A_6(Cpu* c) {bit_b_r(c, c->getA(), 6);}
static void bit_A_7(Cpu* c) {bit_b_r(c, c->getA(), 7);}

static void bit_B_0(Cpu* c) {bit_b_r(c, c->getB(), 0);}
static void bit_B_1(Cpu* c) {bit_b_r(c, c->getB(), 1);}
static void bit_B_2(Cpu* c) {bit_b_r(c, c->getB(), 2);}
static void bit_B_3(Cpu* c) {bit_b_r(c, c->getB(), 3);}
static void bit_B_4(Cpu* c) {bit_b_r(c, c->getB(), 4);}
static void bit_B_5(Cpu* c) {bit_b_r(c, c->getB(), 5);}
static void bit_B_6(Cpu* c) {bit_b_r(c, c->getB(), 6);}
static void bit_B_7(Cpu* c) {bit_b_r(c, c->getB(), 7);}

static void bit_C_0(Cpu* c) {bit_b_r(c, c->getC(), 0);}
static void bit_C_1(Cpu* c) {bit_b_r(c, c->getC(), 1);}
static void bit_C_2(Cpu* c) {bit_b_r(c, c->getC(), 2);}
static void bit_C_3(Cpu* c) {bit_b_r(c, c->getC(), 3);}
static void bit_C_4(Cpu* c) {bit_b_r(c, c->getC(), 4);}
static void bit_C_5(Cpu* c) {bit_b_r(c, c->getC(), 5);}
static void bit_C_6(Cpu* c) {bit_b_r(c, c->getC(), 6);}
static void bit_C_7(Cpu* c) {bit_b_r(c, c->getC(), 7);}


static void bit_D_0(Cpu* c) {bit_b_r(c, c->getD(), 0);}
static void bit_D_1(Cpu* c) {bit_b_r(c, c->getD(), 1);}
static void bit_D_2(Cpu* c) {bit_b_r(c, c->getD(), 2);}
static void bit_D_3(Cpu* c) {bit_b_r(c, c->getD(), 3);}
static void bit_D_4(Cpu* c) {bit_b_r(c, c->getD(), 4);}
static void bit_D_5(Cpu* c) {bit_b_r(c, c->getD(), 5);}
static void bit_D_6(Cpu* c) {bit_b_r(c, c->getD(), 6);}
static void bit_D_7(Cpu* c) {bit_b_r(c, c->getD(), 7);}


static void bit_E_0(Cpu* c) {bit_b_r(c, c->getE(), 0);}
static void bit_E_1(Cpu* c) {bit_b_r(c, c->getE(), 1);}
static void bit_E_2(Cpu* c) {bit_b_r(c, c->getE(), 2);}
static void bit_E_3(Cpu* c) {bit_b_r(c, c->getE(), 3);}
static void bit_E_4(Cpu* c) {bit_b_r(c, c->getE(), 4);}
static void bit_E_5(Cpu* c) {bit_b_r(c, c->getE(), 5);}
static void bit_E_6(Cpu* c) {bit_b_r(c, c->getE(), 6);}
static void bit_E_7(Cpu* c) {bit_b_r(c, c->getE(), 7);}


static void bit_H_0(Cpu* c) {bit_b_r(c, c->getH(), 0);}
static void bit_H_1(Cpu* c) {bit_b_r(c, c->getH(), 1);}
static void bit_H_2(Cpu* c) {bit_b_r(c, c->getH(), 2);}
static void bit_H_3(Cpu* c) {bit_b_r(c, c->getH(), 3);}
static void bit_H_4(Cpu* c) {bit_b_r(c, c->getH(), 4);}
static void bit_H_5(Cpu* c) {bit_b_r(c, c->getH(), 5);}
static void bit_H_6(Cpu* c) {bit_b_r(c, c->getH(), 6);}
static void bit_H_7(Cpu* c) {bit_b_r(c, c->getH(), 7);}


static void bit_L_0(Cpu* c) {bit_b_r(c, c->getL(), 0);}
static void bit_L_1(Cpu* c) {bit_b_r(c, c->getL(), 1);}
static void bit_L_2(Cpu* c) {bit_b_r(c, c->getL(), 2);}
static void bit_L_3(Cpu* c) {bit_b_r(c, c->getL(), 3);}
static void bit_L_4(Cpu* c) {bit_b_r(c, c->getL(), 4);}
static void bit_L_5(Cpu* c) {bit_b_r(c, c->getL(), 5);}
static void bit_L_6(Cpu* c) {bit_b_r(c, c->getL(), 6);}
static void bit_L_7(Cpu* c) {bit_b_r(c, c->getL(), 7);}


static void bit_HL_ind_0(Cpu* c) {
    BYTE addr = c->getHL();
    bit_b_r(c, c->readByte(addr), 0);
}
static void bit_HL_ind_1(Cpu* c) {
    BYTE addr = c->getHL();
    bit_b_r(c, c->readByte(addr), 1);
}
static void bit_HL_ind_2(Cpu* c) {
    BYTE addr = c->getHL();
    bit_b_r(c, c->readByte(addr), 2);
}
static void bit_HL_ind_3(Cpu* c) {
    BYTE addr = c->getHL();
    bit_b_r(c, c->readByte(addr), 3);
}
static void bit_HL_ind_4(Cpu* c) {
    BYTE addr = c->getHL();
    bit_b_r(c, c->readByte(addr), 4);
}
static void bit_HL_ind_5(Cpu* c) {
    BYTE addr = c->getHL();
    bit_b_r(c, c->readByte(addr), 5);
}
static void bit_HL_ind_6(Cpu* c) {
    BYTE addr = c->getHL();
    bit_b_r(c, c->readByte(addr), 6);
}
static void bit_HL_ind_7(Cpu* c) {
    BYTE addr = c->getHL();
    bit_b_r(c, c->readByte(addr), 7);
}

static BYTE set_b_r(Cpu* c, unsigned char r, unsigned char b) {

    //BYTE b = c->readByte(c->getPC());
    c->incPC();

    BYTE temp = (1 << b);

    return (r |= b);
}
static void set_A_0(Cpu* c) {c->setA(set_b_r(c, c->getA(), 0));}
static void set_A_1(Cpu* c) {c->setA(set_b_r(c, c->getA(), 1));}
static void set_A_2(Cpu* c) {c->setA(set_b_r(c, c->getA(), 2));}
static void set_A_3(Cpu* c) {c->setA(set_b_r(c, c->getA(), 3));}
static void set_A_4(Cpu* c) {c->setA(set_b_r(c, c->getA(), 4));}
static void set_A_5(Cpu* c) {c->setA(set_b_r(c, c->getA(), 5));}
static void set_A_6(Cpu* c) {c->setA(set_b_r(c, c->getA(), 6));}
static void set_A_7(Cpu* c) {c->setA(set_b_r(c, c->getA(), 7));}


static void set_B_0(Cpu* c) {c->setB(set_b_r(c, c->getB(), 0));}
static void set_B_1(Cpu* c) {c->setB(set_b_r(c, c->getB(), 1));}
static void set_B_2(Cpu* c) {c->setB(set_b_r(c, c->getB(), 2));}
static void set_B_3(Cpu* c) {c->setB(set_b_r(c, c->getB(), 3));}
static void set_B_4(Cpu* c) {c->setB(set_b_r(c, c->getB(), 4));}
static void set_B_5(Cpu* c) {c->setB(set_b_r(c, c->getB(), 5));}
static void set_B_6(Cpu* c) {c->setB(set_b_r(c, c->getB(), 6));}
static void set_B_7(Cpu* c) {c->setB(set_b_r(c, c->getB(), 7));}

static void set_C_0(Cpu* c) {c->setC(set_b_r(c, c->getC(), 0));}
static void set_C_1(Cpu* c) {c->setC(set_b_r(c, c->getC(), 1));}
static void set_C_2(Cpu* c) {c->setC(set_b_r(c, c->getC(), 2));}
static void set_C_3(Cpu* c) {c->setC(set_b_r(c, c->getC(), 3));}
static void set_C_4(Cpu* c) {c->setC(set_b_r(c, c->getC(), 4));}
static void set_C_5(Cpu* c) {c->setC(set_b_r(c, c->getC(), 5));}
static void set_C_6(Cpu* c) {c->setC(set_b_r(c, c->getC(), 6));}
static void set_C_7(Cpu* c) {c->setC(set_b_r(c, c->getC(), 7));}

static void set_D_0(Cpu* c) {c->setD(set_b_r(c, c->getD(), 0));}
static void set_D_1(Cpu* c) {c->setD(set_b_r(c, c->getD(), 1));}
static void set_D_2(Cpu* c) {c->setD(set_b_r(c, c->getD(), 2));}
static void set_D_3(Cpu* c) {c->setD(set_b_r(c, c->getD(), 3));}
static void set_D_4(Cpu* c) {c->setD(set_b_r(c, c->getD(), 4));}
static void set_D_5(Cpu* c) {c->setD(set_b_r(c, c->getD(), 5));}
static void set_D_6(Cpu* c) {c->setD(set_b_r(c, c->getD(), 6));}
static void set_D_7(Cpu* c) {c->setD(set_b_r(c, c->getD(), 7));}


static void set_E_0(Cpu* c) {c->setE(set_b_r(c, c->getE(), 0));}
static void set_E_1(Cpu* c) {c->setE(set_b_r(c, c->getE(), 1));}
static void set_E_2(Cpu* c) {c->setE(set_b_r(c, c->getE(), 2));}
static void set_E_3(Cpu* c) {c->setE(set_b_r(c, c->getE(), 3));}
static void set_E_4(Cpu* c) {c->setE(set_b_r(c, c->getE(), 4));}
static void set_E_5(Cpu* c) {c->setE(set_b_r(c, c->getE(), 5));}
static void set_E_6(Cpu* c) {c->setE(set_b_r(c, c->getE(), 6));}
static void set_E_7(Cpu* c) {c->setE(set_b_r(c, c->getE(), 7));}


static void set_H_0(Cpu* c) {c->setH(set_b_r(c, c->getH(), 0));}
static void set_H_1(Cpu* c) {c->setH(set_b_r(c, c->getH(), 1));}
static void set_H_2(Cpu* c) {c->setH(set_b_r(c, c->getH(), 2));}
static void set_H_3(Cpu* c) {c->setH(set_b_r(c, c->getH(), 3));}
static void set_H_4(Cpu* c) {c->setH(set_b_r(c, c->getH(), 4));}
static void set_H_5(Cpu* c) {c->setH(set_b_r(c, c->getH(), 5));}
static void set_H_6(Cpu* c) {c->setH(set_b_r(c, c->getH(), 6));}
static void set_H_7(Cpu* c) {c->setH(set_b_r(c, c->getH(), 7));}

static void set_L_0(Cpu* c) {c->setL(set_b_r(c, c->getL(), 0));}
static void set_L_1(Cpu* c) {c->setL(set_b_r(c, c->getL(), 1));}
static void set_L_2(Cpu* c) {c->setL(set_b_r(c, c->getL(), 2));}
static void set_L_3(Cpu* c) {c->setL(set_b_r(c, c->getL(), 3));}
static void set_L_4(Cpu* c) {c->setL(set_b_r(c, c->getL(), 4));}
static void set_L_5(Cpu* c) {c->setL(set_b_r(c, c->getL(), 5));}
static void set_L_6(Cpu* c) {c->setL(set_b_r(c, c->getL(), 6));}
static void set_L_7(Cpu* c) {c->setL(set_b_r(c, c->getL(), 7));}

static void set_HL_ind_0(Cpu* c) {
    BYTE addr = c->getHL();
    BYTE res = set_b_r(c, c->readByte(addr), 0);
    c->writeByte(addr, res);
}
static void set_HL_ind_1(Cpu* c) {
    BYTE addr = c->getHL();
    BYTE res = set_b_r(c, c->readByte(addr), 1);
    c->writeByte(addr, res);
}
static void set_HL_ind_2(Cpu* c) {
    BYTE addr = c->getHL();
    BYTE res = set_b_r(c, c->readByte(addr), 2);
    c->writeByte(addr, res);
}
static void set_HL_ind_3(Cpu* c) {
    BYTE addr = c->getHL();
    BYTE res = set_b_r(c, c->readByte(addr), 3);
    c->writeByte(addr, res);
}
static void set_HL_ind_4(Cpu* c) {
    BYTE addr = c->getHL();
    BYTE res = set_b_r(c, c->readByte(addr), 4);
    c->writeByte(addr, res);
}
static void set_HL_ind_5(Cpu* c) {
    BYTE addr = c->getHL();
    BYTE res = set_b_r(c, c->readByte(addr), 5);
    c->writeByte(addr, res);
}
static void set_HL_ind_6(Cpu* c) {
    BYTE addr = c->getHL();
    BYTE res = set_b_r(c, c->readByte(addr), 6);
    c->writeByte(addr, res);
}
static void set_HL_ind_7(Cpu* c) {
    BYTE addr = c->getHL();
    BYTE res = set_b_r(c, c->readByte(addr), 7);
    c->writeByte(addr, res);
}


static BYTE res_b_r(Cpu* c, unsigned char r, unsigned char b) {

    //BYTE b = c->readByte(c->getPC());
    c->incPC();
    
    BYTE temp = (1 << b);

    return (r &= !b);
}
static void res_A_0(Cpu* c) {c->setA(res_b_r(c, c->getA(), 0));}
static void res_A_1(Cpu* c) {c->setA(res_b_r(c, c->getA(), 1));}
static void res_A_2(Cpu* c) {c->setA(res_b_r(c, c->getA(), 2));}
static void res_A_3(Cpu* c) {c->setA(res_b_r(c, c->getA(), 3));}
static void res_A_4(Cpu* c) {c->setA(res_b_r(c, c->getA(), 4));}
static void res_A_5(Cpu* c) {c->setA(res_b_r(c, c->getA(), 5));}
static void res_A_6(Cpu* c) {c->setA(res_b_r(c, c->getA(), 6));}
static void res_A_7(Cpu* c) {c->setA(res_b_r(c, c->getA(), 7));}

static void res_B_0(Cpu* c) {c->setB(res_b_r(c, c->getB(), 0));}
static void res_B_1(Cpu* c) {c->setB(res_b_r(c, c->getB(), 1));}
static void res_B_2(Cpu* c) {c->setB(res_b_r(c, c->getB(), 2));}
static void res_B_3(Cpu* c) {c->setB(res_b_r(c, c->getB(), 3));}
static void res_B_4(Cpu* c) {c->setB(res_b_r(c, c->getB(), 4));}
static void res_B_5(Cpu* c) {c->setB(res_b_r(c, c->getB(), 5));}
static void res_B_6(Cpu* c) {c->setB(res_b_r(c, c->getB(), 6));}
static void res_B_7(Cpu* c) {c->setB(res_b_r(c, c->getB(), 7));}

static void res_C_0(Cpu* c) {c->setC(res_b_r(c, c->getC(), 0));}
static void res_C_1(Cpu* c) {c->setC(res_b_r(c, c->getC(), 1));}
static void res_C_2(Cpu* c) {c->setC(res_b_r(c, c->getC(), 2));}
static void res_C_3(Cpu* c) {c->setC(res_b_r(c, c->getC(), 3));}
static void res_C_4(Cpu* c) {c->setC(res_b_r(c, c->getC(), 4));}
static void res_C_5(Cpu* c) {c->setC(res_b_r(c, c->getC(), 5));}
static void res_C_6(Cpu* c) {c->setC(res_b_r(c, c->getC(), 6));}
static void res_C_7(Cpu* c) {c->setC(res_b_r(c, c->getC(), 7));}

static void res_D_0(Cpu* c) {c->setD(res_b_r(c, c->getD(), 0));}
static void res_D_1(Cpu* c) {c->setD(res_b_r(c, c->getD(), 1));}
static void res_D_2(Cpu* c) {c->setD(res_b_r(c, c->getD(), 2));}
static void res_D_3(Cpu* c) {c->setD(res_b_r(c, c->getD(), 3));}
static void res_D_4(Cpu* c) {c->setD(res_b_r(c, c->getD(), 4));}
static void res_D_5(Cpu* c) {c->setD(res_b_r(c, c->getD(), 5));}
static void res_D_6(Cpu* c) {c->setD(res_b_r(c, c->getD(), 6));}
static void res_D_7(Cpu* c) {c->setD(res_b_r(c, c->getD(), 7));}

static void res_E_0(Cpu* c) {c->setE(res_b_r(c, c->getE(), 0));}
static void res_E_1(Cpu* c) {c->setE(res_b_r(c, c->getE(), 1));}
static void res_E_2(Cpu* c) {c->setE(res_b_r(c, c->getE(), 2));}
static void res_E_3(Cpu* c) {c->setE(res_b_r(c, c->getE(), 3));}
static void res_E_4(Cpu* c) {c->setE(res_b_r(c, c->getE(), 4));}
static void res_E_5(Cpu* c) {c->setE(res_b_r(c, c->getE(), 5));}
static void res_E_6(Cpu* c) {c->setE(res_b_r(c, c->getE(), 6));}
static void res_E_7(Cpu* c) {c->setE(res_b_r(c, c->getE(), 7));}

static void res_H_0(Cpu* c) {c->setH(res_b_r(c, c->getH(), 0));}
static void res_H_1(Cpu* c) {c->setH(res_b_r(c, c->getH(), 1));}
static void res_H_2(Cpu* c) {c->setH(res_b_r(c, c->getH(), 2));}
static void res_H_3(Cpu* c) {c->setH(res_b_r(c, c->getH(), 3));}
static void res_H_4(Cpu* c) {c->setH(res_b_r(c, c->getH(), 4));}
static void res_H_5(Cpu* c) {c->setH(res_b_r(c, c->getH(), 5));}
static void res_H_6(Cpu* c) {c->setH(res_b_r(c, c->getH(), 6));}
static void res_H_7(Cpu* c) {c->setH(res_b_r(c, c->getH(), 7));}

static void res_L_0(Cpu* c) {c->setL(res_b_r(c, c->getL(), 0));}
static void res_L_1(Cpu* c) {c->setL(res_b_r(c, c->getL(), 1));}
static void res_L_2(Cpu* c) {c->setL(res_b_r(c, c->getL(), 2));}
static void res_L_3(Cpu* c) {c->setL(res_b_r(c, c->getL(), 3));}
static void res_L_4(Cpu* c) {c->setL(res_b_r(c, c->getL(), 4));}
static void res_L_5(Cpu* c) {c->setL(res_b_r(c, c->getL(), 5));}
static void res_L_6(Cpu* c) {c->setL(res_b_r(c, c->getL(), 6));}
static void res_L_7(Cpu* c) {c->setL(res_b_r(c, c->getL(), 7));}

static void res_HL_ind_0(Cpu* c) {
    BYTE addr = c->getHL();
    BYTE res = res_b_r(c, c->readByte(addr), 0);
    c->writeByte(addr, res);
}
static void res_HL_ind_1(Cpu* c) {
    BYTE addr = c->getHL();
    BYTE res = res_b_r(c, c->readByte(addr), 1);
    c->writeByte(addr, res);
}
static void res_HL_ind_2(Cpu* c) {
    BYTE addr = c->getHL();
    BYTE res = res_b_r(c, c->readByte(addr), 2);
    c->writeByte(addr, res);
}
static void res_HL_ind_3(Cpu* c) {
    BYTE addr = c->getHL();
    BYTE res = res_b_r(c, c->readByte(addr), 3);
    c->writeByte(addr, res);
}
static void res_HL_ind_4(Cpu* c) {
    BYTE addr = c->getHL();
    BYTE res = res_b_r(c, c->readByte(addr), 4);
    c->writeByte(addr, res);
}
static void res_HL_ind_5(Cpu* c) {
    BYTE addr = c->getHL();
    BYTE res = res_b_r(c, c->readByte(addr), 5);
    c->writeByte(addr, res);
}
static void res_HL_ind_6(Cpu* c) {
    BYTE addr = c->getHL();
    BYTE res = res_b_r(c, c->readByte(addr), 6);
    c->writeByte(addr, res);
}
static void res_HL_ind_7(Cpu* c) {
    BYTE addr = c->getHL();
    BYTE res = res_b_r(c, c->readByte(addr), 7);
    c->writeByte(addr, res);
}


static void jp(Cpu* c) {
   
    BYTE ls = c->readByte(c->getPC());
    c->incPC();
    BYTE ms = c->readByte(c->getPC());
    
    c->setPC((ms << 8) + ls);
}
static void jp_nz(Cpu* c) {
    if(!c->isFlagZero())
        jp(c);
}
static void jp_z(Cpu* c) {
    if(c->isFlagZero())
        jp(c);
}
static void jp_nc(Cpu* c) {
    if(!c->isFlagCarry())
        jp(c);
}
static void jp_c(Cpu* c) {
    if(c->isFlagCarry())
        jp(c);
}
static void jp_hl_ind(Cpu* c) {c->setPC(c->getHL());}
static void jr(Cpu* c) {
    signed char n = c->readByte(c->getPC());
    c->setPC(c->getPC() + n);
}
static void jr_nz(Cpu* c) {
    if(!c->isFlagZero())
        jr(c);
}
static void jr_z(Cpu* c) {
    if(c->isFlagZero())
        jr(c);
}
static void jr_nc(Cpu* c) {
    if(!c->isFlagCarry())
        jr(c);
}
static void jr_c(Cpu* c) {
    if(c->isFlagCarry())
        jr(c);
}
static void call(Cpu* c) {
    WORD oldPC = c->readWord(c->getPC());
    c->pushWord(oldPC + 2);

    jp(c);
}
static void call_nz(Cpu* c) {
    if(!c->isFlagZero())
        call(c);
}
static void call_z(Cpu* c) {
    if(c->isFlagZero())
        call(c);
}
static void call_nc(Cpu* c) {
    if(!c->isFlagCarry())
        call(c);
}
static void call_c(Cpu* c) {
    if(c->isFlagCarry())
        call(c);
}
static void rst(Cpu* c, unsigned char ls) {
    c->pushWord(c->getPC());

    c->setPC(0x0000 + ls);
}
static void rst_0(Cpu* c) {rst(c, 0x00);}
static void rst_8(Cpu* c) {rst(c, 0x08);}
static void rst_10(Cpu* c) {rst(c, 0x10);}
static void rst_18(Cpu* c) {rst(c, 0x18);}
static void rst_20(Cpu* c) {rst(c, 0x20);}
static void rst_28(Cpu* c) {rst(c, 0x28);}
static void rst_30(Cpu* c) {rst(c, 0x30);}
static void rst_38(Cpu* c) {rst(c, 0x38);}

static void ret(Cpu* c) {
    WORD addr = c->popWord();
    c->setPC(addr);
}
static void ret_nz(Cpu* c) {
    if(!c->isFlagZero())
        ret(c);
}
static void ret_z(Cpu* c) {
    if(c->isFlagZero())
        ret(c);
}
static void ret_nc(Cpu* c) {
    if(!c->isFlagCarry())
        ret(c);
}
static void ret_c(Cpu* c) {
    if(c->isFlagCarry())
        ret(c);
}
static void reti(Cpu* c) {
    ret(c);
    ei(c);
}

static void cb(Cpu* c) {
    WORD oldPC = c->getPC();
    c->incPC();

    c->getInstrSetCBPrefixAt(oldPC).function(c);
}






