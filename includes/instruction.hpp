#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "cpu.hpp"
#include <string>
#include <map>

//class Cpu;

struct instruction {
    std::string name;
    int cycles;
    int paramNum;
    void (*function)(Cpu*);

    //constructor
    instruction(std::string, int, int, void(*)(Cpu*));
};
//std::map<unsigned char, instruction> instrSet;
void init(std::map<unsigned char, instruction>&);
instruction getInstr(unsigned char);


//________________________________ 8/bit Arithmetic_____________________________

//------------------- NOT_DEFINED -------------------
static void not_defined(void);

//------------------- ADD -------------------
static void add(Cpu*, unsigned char);
static void add_A_B(Cpu*);
static void add_A_B(Cpu*);
static void add_A_C(Cpu*);
static void add_A_D(Cpu*);
static void add_A_E(Cpu*);
static void add_A_H(Cpu*);
static void add_A_L(Cpu*);
static void add_A_A(Cpu*);
static void add_A_HL_ind(Cpu*);
static void add_A_n(Cpu*, unsigned char);
//------------------- ADC -------------------
static void adc(Cpu*, unsigned char);
static void adc_A_B(Cpu*);
static void adc_A_B(Cpu*);
static void adc_A_C(Cpu*);
static void adc_A_D(Cpu*);
static void adc_A_E(Cpu*);
static void adc_A_H(Cpu*);
static void adc_A_L(Cpu*);
static void adc_A_A(Cpu*);
static void adc_A_HL_ind(Cpu*);
static void adc_A_n(Cpu*, unsigned char);
//------------------- SUB -------------------
static void sub(Cpu* ,unsigned char);
static void sub_A_B(Cpu*);
static void sub_A_C(Cpu*);
static void sub_A_D(Cpu*);
static void sub_A_E(Cpu*);
static void sub_A_H(Cpu*);
static void sub_A_L(Cpu*);
static void sub_A_A(Cpu*);
static void sub_A_HL_ind(Cpu*);
static void sub_A_n(Cpu*, unsigned char);
//------------------- SDC -------------------
static void sbc(Cpu*, unsigned char);
static void sbc_A_B(Cpu*);
static void sbc_A_B(Cpu*);
static void sbc_A_C(Cpu*);
static void sbc_A_D(Cpu*);
static void sbc_A_E(Cpu*);
static void sbc_A_H(Cpu*);
static void sbc_A_L(Cpu*);
static void sbc_A_A(Cpu*);
static void sbc_A_HL_ind(Cpu*);
//static void sbc_A_n(Cpu*, unsigned char); -> maybe does not exist
//------------------- AND -------------------
static void and_(Cpu*, unsigned char);
static void and_A_B(Cpu*);
static void and_A_B(Cpu*);
static void and_A_C(Cpu*);
static void and_A_D(Cpu*);
static void and_A_E(Cpu*);
static void and_A_H(Cpu*);
static void and_A_L(Cpu*);
static void and_A_A(Cpu*);
static void and_A_HL_ind(Cpu*);
static void and_A_n(Cpu*, unsigned char);
//------------------- OR -------------------
static void or_(Cpu*, unsigned char);
static void or_A_B(Cpu*);
static void or_A_B(Cpu*);
static void or_A_C(Cpu*);
static void or_A_D(Cpu*);
static void or_A_E(Cpu*);
static void or_A_H(Cpu*);
static void or_A_L(Cpu*);
static void or_A_A(Cpu*);
static void or_A_HL_ind(Cpu*);
static void or_A_n(Cpu*, unsigned char);
//------------------- XOR -------------------
static void xor_(Cpu*, unsigned char);
static void xor_A_B(Cpu*);
static void xor_A_B(Cpu*);
static void xor_A_C(Cpu*);
static void xor_A_D(Cpu*);
static void xor_A_E(Cpu*);
static void xor_A_H(Cpu*);
static void xor_A_L(Cpu*);
static void xor_A_A(Cpu*);
static void xor_A_HL_ind(Cpu*);
static void xor_A_n(Cpu*, unsigned char);
//------------------- CP -------------------
static void cp_(Cpu*, unsigned char);
static void cp_A_B(Cpu*);
static void cp_A_B(Cpu*);
static void cp_A_C(Cpu*);
static void cp_A_D(Cpu*);
static void cp_A_E(Cpu*);
static void cp_A_H(Cpu*);
static void cp_A_L(Cpu*);
static void cp_A_A(Cpu*);
static void cp_A_HL_ind(Cpu*);
static void cp_A_n(Cpu*, unsigned char);
//------------------- INC -------------------
static BYTE inc(Cpu*, unsigned char);
static void inc_A_B(Cpu*);
static void inc_A_B(Cpu*);
static void inc_A_C(Cpu*);
static void inc_A_D(Cpu*);
static void inc_A_E(Cpu*);
static void inc_A_H(Cpu*);
static void inc_A_L(Cpu*);
static void inc_A_A(Cpu*);
static void inc_A_HL_ind(Cpu*);
//------------------- DEC -------------------
static BYTE dec(Cpu*, unsigned char);
static void dec_A_B(Cpu*);
static void dec_A_B(Cpu*);
static void dec_A_C(Cpu*);
static void dec_A_D(Cpu*);
static void dec_A_E(Cpu*);
static void dec_A_H(Cpu*);
static void dec_A_L(Cpu*);
static void dec_A_A(Cpu*);
static void dec_A_HL_ind(Cpu*);

//________________________________ 8/bit Arithmetic_____________________________

//------------------- ADD HL -------------------
static void add_HL(Cpu*, BYTE);
static void add_HL_BC(Cpu*);
static void add_HL_DE(Cpu*);
static void add_HL_HL(Cpu*);
static void add_HL_SP(Cpu*);
//------------------- ADD Sp, n -------------------
static void add_SP_n(Cpu*);
//------------------- INC nn -------------------
static void inc_HL(Cpu*);
static void inc_SP(Cpu*);
static void inc_DE(Cpu*);
static void inc_BC(Cpu*);
//------------------- DEC nn -------------------
static void dec_HL(Cpu*);
static void dec_SP(Cpu*);
static void dec_DE(Cpu*);
static void dec_BC(Cpu*);

//________________________________ Miscellaneous _____________________________

//------------------- SWAP n -------------------
BYTE swap_n(Cpu*, unsigned char);
static void swap_A(Cpu*);
static void swap_B(Cpu*);
static void swap_C(Cpu*);
static void swap_D(Cpu*);
static void swap_E(Cpu*);
static void swap_H(Cpu*);
static void swap_L(Cpu*);
static void swap_HL(Cpu*);
//------------------- SWAP n -------------------
static void daa(Cpu*);
//------------------- CPL n -------------------
static void cpl(Cpu*);
//------------------- CCF -------------------
static void ccf(Cpu*);
//------------------- SCF -------------------
static void scf(Cpu*);
//------------------- NOP -------------------
static void nop(void);
//------------------- HALT -------------------
static void halt(void);
//------------------- STOP -------------------
static void stop(void);
//------------------- DI -------------------
static void di(Cpu*);
//------------------- EI -------------------
static void ei(Cpu*);

//________________________________ Rotates and shifts _____________________________

//------------------- RLCA -------------------
static void rlca(Cpu*);
//------------------- RLA -------------------
static void rla(Cpu*);






#endif