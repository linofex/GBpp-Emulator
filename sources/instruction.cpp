#include "../includes/instruction.hpp"
#include <iostream>
#include <map>

instruction::instruction(std::string name, int cycles, int paramNum, void (*f)(Cpu*)) {
	this->name = name;
    this->cycles = cycles;
	this->paramNum = paramNum;
	function = f;
}


//std::map<unsigned char, int> a;

//a[0x80] = {20};

//std::map<unsigned char, instruction> instrSet;

//instruction i = instruction("ADD A, B", 4, 0, add_A_B);
//instrSet[0x80] = i;

/* instrSet[0x80] = instruction("ADD A, B", 4, 0, add_A_B);
instrSet[0x81] = instruction("ADD A, C", 4, 0, add_A_C);
 */
instruction instrSet2[2] = {
	instruction("ADD_A_B", 4, 0, add_A_B),
    instruction("ADD_A_C", 4, 0, add_A_C)
}; 

//std::map<unsigned char, struct instruction> instrSet;

void init(std::map<unsigned char, instruction>& instrSet) {
    //std::cout<<typeid(i).name()<<std::endl;
    instrSet.insert(std::make_pair(0x80, instruction("ADD A, B", 4, 0, add_A_B)));  
    instrSet.insert(std::make_pair(0x81, instruction("ADD A, C", 4, 0, add_A_C)));
    instrSet.insert(std::make_pair(0x82, instruction("ADD A, D", 4, 0, add_A_D)));
    instrSet.insert(std::make_pair(0x83, instruction("ADD A, E", 4, 0, add_A_E)));  
    instrSet.insert(std::make_pair(0x84, instruction("ADD A, H", 4, 0, add_A_H)));
    instrSet.insert(std::make_pair(0x85, instruction("ADD A, L", 4, 0, add_A_L)));
    instrSet.insert(std::make_pair(0x86, instruction("ADD A, (HL)", 8, 0, add_A_HL_ind)));  
    instrSet.insert(std::make_pair(0x87, instruction("ADD A, A", 4, 0, add_A_A)));
    //instrSet.insert(std::make_pair(0xC6, instruction("ADD A, #", 8, 0, add_A_n))); ->>>>>>>>>>>>>> da rivedere il parametro unsigned char

    instrSet.insert(std::make_pair(0x88, instruction("ADC A, B", 4, 0, adc_A_B)));  
    instrSet.insert(std::make_pair(0x89, instruction("ADC A, C", 4, 0, adc_A_C)));
    instrSet.insert(std::make_pair(0x8A, instruction("ADC A, D", 4, 0, adc_A_D)));
    instrSet.insert(std::make_pair(0x8B, instruction("ADC A, E", 4, 0, adc_A_E)));  
    instrSet.insert(std::make_pair(0x8C, instruction("ADC A, H", 4, 0, adc_A_H)));
    instrSet.insert(std::make_pair(0x8D, instruction("ADC A, L", 4, 0, adc_A_L)));
    instrSet.insert(std::make_pair(0x8E, instruction("ADC A, (HL)", 8, 0, adc_A_HL_ind)));  
    instrSet.insert(std::make_pair(0x8F, instruction("ADC A, A", 4, 0, adc_A_A)));  
    //instrSet.insert(std::make_pair(0xCE, instruction("ADC A, #", 8, 0, adc_A_n))); ->>>>>>>>>>>>>> da rivedere il parametro unsigned char

    instrSet.insert(std::make_pair(0x90, instruction("SUB A, B", 4, 0, sub_A_B)));  
    instrSet.insert(std::make_pair(0x91, instruction("SUB A, C", 4, 0, sub_A_C)));
    instrSet.insert(std::make_pair(0x92, instruction("SUB A, D", 4, 0, sub_A_D)));
    instrSet.insert(std::make_pair(0x93, instruction("SUB A, E", 4, 0, sub_A_E)));  
    instrSet.insert(std::make_pair(0x94, instruction("SUB A, H", 4, 0, sub_A_H)));
    instrSet.insert(std::make_pair(0x95, instruction("SUB A, L", 4, 0, sub_A_L)));
    instrSet.insert(std::make_pair(0x96, instruction("SUB A, (HL)", 8, 0, sub_A_HL_ind)));  
    instrSet.insert(std::make_pair(0x97, instruction("SUB A, A", 4, 0, sub_A_A)));  
    //instrSet.insert(std::make_pair(0xD6, instruction("SUB A, #", 8, 0, sub_A_n))); ->>>>>>>>>>>>>> da rivedere il parametro unsigned char

    instrSet.insert(std::make_pair(0x98, instruction("SBC A, B", 4, 0, sbc_A_B)));  
    instrSet.insert(std::make_pair(0x99, instruction("SBC A, C", 4, 0, sbc_A_C)));
    instrSet.insert(std::make_pair(0x9A, instruction("SBC A, D", 4, 0, sbc_A_D)));
    instrSet.insert(std::make_pair(0x9B, instruction("SBC A, E", 4, 0, sbc_A_E)));  
    instrSet.insert(std::make_pair(0x9C, instruction("SBC A, H", 4, 0, sbc_A_H)));
    instrSet.insert(std::make_pair(0x9D, instruction("SBC A, L", 4, 0, sbc_A_L)));
    instrSet.insert(std::make_pair(0x9E, instruction("SBC A, (HL)", 8, 0, sbc_A_HL_ind)));  
    instrSet.insert(std::make_pair(0x9F, instruction("SBC A, A", 4, 0, sbc_A_A)));  
    //instrSet.insert(std::make_pair(0xD6, instruction("SBC A, #", 8, 0, sbc_A_n))); ->>>>>>>>>>>>>> forse non esiste


    //std::cout<<"---------------------------------------------> "<<instrSet.at(0x80).name<<std::endl;

}

/* instruction getInstr(unsigned char opcode) {
    unsigned char temp = 0x80;
    return instrSet2[0];
} */


//----------------------- EMPTY -------------------------------------
static void not_defined() {
    std::cout<<"Instruction not defined"<<std::endl;
}

//-----------------------ADD-------------------------------------
static void add(Cpu* c, unsigned char n) {
   std::cout<<"inizio add"<<std::endl;

   int res = c->getA() + (int) n;
    
    if(res == 0)        //sum = 0
        c->setFlag(flagZ);
    else
        c->resetFlag(flagZ);

    c->setA(res);

    // if(res < 0)     //sum < 0
    //    setFlag(flagN);
    //else
    //    resetFlag(flagN);
        
    if(res > 255)  //sum overflow
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
static void add_A_n(Cpu* c, unsigned char n) {add(c, n);}
static void add_A_HL_ind(Cpu* c) {
    WORD addr = c->getHL();
    unsigned char n = c->readByte(addr);
    add(c, n);
}

static void adc(Cpu* c, unsigned char n) {
    int carry = c->isFlagCarry() ? 1 : 0;  //carry = 1 or 0
    add(c, n + carry);
}
static void adc_A_B(Cpu* c) {adc(c, c->getB());}
static void adc_A_C(Cpu* c) {adc(c, c->getC());}
static void adc_A_D(Cpu* c) {adc(c, c->getD());}
static void adc_A_E(Cpu* c) {adc(c, c->getE());}
static void adc_A_H(Cpu* c) {adc(c, c->getH());}
static void adc_A_L(Cpu* c) {adc(c, c->getL());}
static void adc_A_A(Cpu* c) {adc(c, c->getA());}
static void adc_A_n(Cpu* c, unsigned char n) {adc(c, n);}
static void adc_A_HL_ind(Cpu* c) {
    WORD addr = c->getHL();
    unsigned char n = c->readByte(addr);
    adc(c, n);
}

static void sub(Cpu* c, unsigned char n) {
    int res = c->getA() - (int) n;

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
        
    if(((n & 0x0F) + (c->getA() & 0x0F)) < 0)    //if borrow from bit 3
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
static void sub_A_n(Cpu* c, unsigned char n) {sub(c, n);}
static void sub_A_HL_ind(Cpu* c) {
    WORD addr = c->getHL();
    unsigned char n = c->readByte(addr);
    sub(c, n);
}

static void sbc(Cpu* c, unsigned char n) {
    int carry = c->isFlagCarry() ? 1 : 0;  //carry = 1 or 0
    sub(c, n + carry);
}
static void sbc_A_B(Cpu* c) {sbc(c, c->getB());}
static void sbc_A_C(Cpu* c) {sbc(c, c->getC());}
static void sbc_A_D(Cpu* c) {sbc(c, c->getD());}
static void sbc_A_E(Cpu* c) {sbc(c, c->getE());}
static void sbc_A_H(Cpu* c) {sbc(c, c->getH());}
static void sbc_A_L(Cpu* c) {sbc(c, c->getL());}
static void sbc_A_A(Cpu* c) {sbc(c, c->getA());}
//static void sbc_A_n(Cpu* c, unsigned char n) {sbc(c, n);} -> maybe does not exists
static void sbc_A_HL_ind(Cpu* c) {
    WORD addr = c->getHL();
    unsigned char n = c->readByte(addr);
    sbc(c, n);
}

static void and_(Cpu* c, unsigned char n) {
    int res = c->getA() & (int) n;

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
static void and_A_n(Cpu* c, unsigned char n) {and_(c, n);}
static void and_A_HL_ind(Cpu* c) {
    WORD addr = c->getHL();
    unsigned char n = c->readByte(addr);
    and_(c, n);
}

static void or_(Cpu* c, unsigned char n) {
    int res = c->getA() | (int) n;

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
static void or_A_n(Cpu* c, unsigned char n) {or_(c, n);}
static void or_A_HL_ind(Cpu* c) {
    WORD addr = c->getHL();
    unsigned char n = c->readByte(addr);
    or_(c, n);
}

static void xor_(Cpu* c, unsigned char n) {
    int res;
    res = res ? !n : n;

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
static void xor_A_n(Cpu* c, unsigned char n) {xor_(c, n);}
static void xor_A_HL_ind(Cpu* c) {
    WORD addr = c->getHL();
    unsigned char n = c->readByte(addr);
    xor_(c, n);
}

static void cp(Cpu* c, unsigned char n) {
    int res = c->getA() - (int) n;

    if(res == 0)        //sub = 0
        c->setFlag(flagZ);
    else
        c->resetFlag(flagZ);
    
    c->setFlag(flagN);
        
    if(res < 0)  //sub with borrow
        c->setFlag(flagC);
    else
        c->resetFlag(flagC);
        
    if(((n & 0x0F) + (c->getA() & 0x0F)) < 0)    //if borrow from bit 3
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
static void cp_A_n(Cpu* c, unsigned char n) {cp(c, n);}
static void cp_A_HL_ind(Cpu* c) {
    WORD addr = c->getHL();
    unsigned char n = c->readByte(addr);
    cp(c, n);
}

static BYTE inc(Cpu* c, unsigned char n) {
    int res = n + 1;

    if(res == 0)        //res = 0
        c->setFlag(flagZ);
    else
        c->resetFlag(flagZ);
    
    c->resetFlag(flagN);
        
    if((res & 0x0F) > 0x0F)    //if carry from bit 3
        c->setFlag(flagH);
    else
        c->resetFlag(flagH);

    return res;
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
    int res = n - 1;

    if(res == 0)        //res = 0
        c->setFlag(flagZ);
    else
        c->resetFlag(flagZ);
    
    c->setFlag(flagN);
        
    if((res & 0x0F) < 0)    //if borrow from bit 3
        c->setFlag(flagH);
    else
        c->resetFlag(flagH);

    return res;
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

static void add_HL(Cpu* c, BYTE val) {
    
    unsigned long res = c->getHL() + val;

    c->setHL((unsigned short)(res & 0xFFFF));
 
    c->resetFlag(flagN);

    if(res & 0xFFFF0000)
        c->setFlag(flagC);
    else
        c->resetFlag(flagC);
    
    if(((c->getHL() & 0x0F) + (val & 0x0F)) > 0x0F)
        c->setFlag(flagH);
	else
        c->resetFlag(flagH);
}
static void add_HL_BC(Cpu* c) {add_HL(c, c->getBC());};
static void add_HL_DE(Cpu* c) {add_HL(c, c->getDE());};
static void add_HL_HL(Cpu* c) {add_HL(c, c->getHL());};
static void add_HL_SP(Cpu* c) {add_HL(c, c->getSP());};

static void add_SP_n(Cpu* c, unsigned char n) {
    c->resetFlag(flagZ);
    c->resetFlag(flagN);

    unsigned long res = c->getSP() + n;

    c->setSP((unsigned short)(res & 0xFFFF));
 
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
static void inc_SP(Cpu* c) {c->setSP(c->getSP() + 1);};
static void inc_DE(Cpu* c) {c->setDE(c->getDE() + 1);};
static void inc_BC(Cpu* c) {c->setBC(c->getBC() + 1);};

static void dec_HL(Cpu* c) {c->setHL(c->getHL() - 1);};
static void dec_SP(Cpu* c) {c->setSP(c->getSP() - 1);};
static void dec_DE(Cpu* c) {c->setDE(c->getDE() - 1);};
static void dec_BC(Cpu* c) {c->setBC(c->getBC() - 1);};

BYTE swap_n(Cpu* c, unsigned char n) {
    c->resetFlag(flagN);
    c->resetFlag(flagH);
    c->resetFlag(flagC);

    BYTE high = n & 0xFFFF0000;
    BYTE low = n & 0x0000FFFF;
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
static void swap_HL(Cpu* c) {
    WORD addr = c->getHL();
    unsigned char n = c->readByte(addr);
    c->setHL(swap_n(c, c->getHL()));    
}

static void daa(Cpu* c) {
    //manca-------------------------------->>>>>>>>>>>>>>>>>>>>>>>>>>>>
}

static void cpl(Cpu* c) {
    c->setFlag(flagN);
    c->setFlag(flagH);

    c->setA(~c->getA());
}
static void ccf(Cpu* c) {
    int carry = c->isFlagCarry() ? 1 : 0;
    c->setFlag(~carry);
    c->resetFlag(flagH);
    c->resetFlag(flagN);
}
static void scf(Cpu* c) {
    c->setFlag(flagC);
    c->resetFlag(flagH);
    c->resetFlag(flagN);
}
static void nop() {}
static void halt() {}   //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
static void stop() {}   //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
static void di(Cpu* c) {}//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
static void ei(Cpu* c) {}//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
static void rlca(Cpu* c) {
    c->resetFlag(flagN);
    c->resetFlag(flagH);

    BYTE a = c->getA();
    BYTE carry = 0;//((a & 0xF0000000) >> 7) ? c->setFlag(flagC) : c->resetFlag(flagC); //_______________________
    a <<= 1;
    a += carry;
    if(a == 0)
        c->setFlag(flagZ);
    else
        c->resetFlag(flagZ);
    c->setA(a);
}
static void rla(Cpu* c) {}  //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>