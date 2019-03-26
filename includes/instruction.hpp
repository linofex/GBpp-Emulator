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
//instruction getInstr(unsigned char);


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
static void add_A_n(Cpu*);
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
static void adc_A_n(Cpu*);
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
static void sub_A_n(Cpu*);
//------------------- SDC -------------------
static void sbc(Cpu*, unsigned char);
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
static void and_A_n(Cpu*);
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
static void or_A_n(Cpu*);
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
static void xor_A_n(Cpu*);
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
static void cp_A_n(Cpu*);
//------------------- INC -------------------
static BYTE inc(Cpu*, unsigned char);
static void inc_A(Cpu*);
static void inc_B(Cpu*);
static void inc_C(Cpu*);
static void inc_D(Cpu*);
static void inc_E(Cpu*);
static void inc_H(Cpu*);
static void inc_L(Cpu*);
static void inc_HL_ind(Cpu*);
//------------------- DEC -------------------
static BYTE dec(Cpu*, unsigned char);
static void dec_B(Cpu*);
static void dec_C(Cpu*);
static void dec_D(Cpu*);
static void dec_E(Cpu*);
static void dec_H(Cpu*);
static void dec_L(Cpu*);
static void dec_A(Cpu*);
static void dec_HL_ind(Cpu*);

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


//________________________________ 8-bit Load _____________________________

//------------------- LOAD nn, n -------------------
static void load_B_n(Cpu*, unsigned char);
static void load_C_n(Cpu*, unsigned char);
static void load_D_n(Cpu*, unsigned char);
static void load_E_n(Cpu*, unsigned char);
static void load_H_n(Cpu*, unsigned char);
static void load_L_n(Cpu*, unsigned char);

//------------------- LOAD nn, n -------------------
static void load_A_A(Cpu*);
static void load_A_B(Cpu*);
static void load_A_C(Cpu*);
static void load_A_D(Cpu*);
static void load_A_E(Cpu*);
static void load_A_H(Cpu*);
static void load_A_L(Cpu*);
static void load_A_HL(Cpu*);

static void load_B_B(Cpu*);
static void load_B_C(Cpu*);
static void load_B_D(Cpu*);
static void load_B_E(Cpu*);
static void load_B_H(Cpu*);
static void load_B_L(Cpu*);
static void load_B_HL(Cpu*);

static void load_C_A(Cpu*);
static void load_C_B(Cpu*);
static void load_C_C(Cpu*);
static void load_C_D(Cpu*);
static void load_C_E(Cpu*);
static void load_C_H(Cpu*);
static void load_C_L(Cpu*);
static void load_C_HL(Cpu*);

static void load_D_B(Cpu*);
static void load_D_C(Cpu*);
static void load_D_D(Cpu*);
static void load_D_E(Cpu*);
static void load_D_H(Cpu*);
static void load_D_L(Cpu*);
static void load_D_HL(Cpu*);

static void load_E_A(Cpu*);
static void load_E_B(Cpu*);
static void load_E_C(Cpu*);
static void load_E_D(Cpu*);
static void load_E_E(Cpu*);
static void load_E_H(Cpu*);
static void load_E_L(Cpu*);
static void load_E_HL(Cpu*);

static void load_H_B(Cpu*);
static void load_H_C(Cpu*);
static void load_H_D(Cpu*);
static void load_H_E(Cpu*);
static void load_H_H(Cpu*);
static void load_H_L(Cpu*);
static void load_H_HL(Cpu*);

static void load_L_B(Cpu*);
static void load_L_C(Cpu*);
static void load_L_D(Cpu*);
static void load_L_E(Cpu*);
static void load_L_H(Cpu*);
static void load_L_L(Cpu*);
static void load_L_HL(Cpu*);

static void load_HL_ind_x(Cpu* c, unsigned char);
static void load_HL_ind_B(Cpu*);
static void load_HL_ind_C(Cpu*);
static void load_HL_ind_D(Cpu*);
static void load_HL_ind_E(Cpu*);
static void load_HL_ind_H(Cpu*);
static void load_HL_ind_L(Cpu*);
static void load_HL_ind_n(Cpu*, unsigned char);

static void load_A_x_ind(Cpu* c, unsigned short);
static void load_A_BC_ind(Cpu*);
static void load_A_DE_ind(Cpu*);
static void load_A_HL_ind(Cpu*);
static void load_A_NN_ind(Cpu*, unsigned short);
static void load_A_n(Cpu*, unsigned char);








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