#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "cpu.hpp"
#include <string>

class Cpu;
struct instruction {
    std::string name;
    int cycles;
    int paramNum;
    void (*function)(Cpu*);

    //constructor
    instruction(std::string, int, int, void(*)(Cpu*));
};
instruction getInstr(unsigned char);
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











#endif