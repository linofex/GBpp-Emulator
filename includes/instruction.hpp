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
void initCBPrefix(std::map<unsigned char, instruction>&);
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




//________________________________ CB Extended Instr _____________________________

//------------------- CB -------------------
static void cb(Cpu*);



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

//------------------- RLC n -------------------
static BYTE rlc(Cpu*, unsigned char);
static void rlc_A(Cpu*);
static void rlc_B(Cpu*);
static void rlc_C(Cpu*);
static void rlc_D(Cpu*);
static void rlc_E(Cpu*);
static void rlc_H(Cpu*);
static void rlc_L(Cpu*);
static void rlc_HL_ind(Cpu*);
//------------------- RL n -------------------
static BYTE rl(Cpu*, unsigned char);
static void rl_A(Cpu*);
static void rl_B(Cpu*);
static void rl_C(Cpu*);
static void rl_D(Cpu*);
static void rl_E(Cpu*);
static void rl_H(Cpu*);
static void rl_L(Cpu*);
static void rl_HL_ind(Cpu*);
//------------------- RRC n -------------------
static BYTE rrc(Cpu*, unsigned char);
static void rrc_A(Cpu*);
static void rrc_B(Cpu*);
static void rrc_C(Cpu*);
static void rrc_D(Cpu*);
static void rrc_E(Cpu*);
static void rrc_H(Cpu*);
static void rrc_L(Cpu*);
static void rrc_HL_ind(Cpu*);
//------------------- RR n -------------------
static BYTE rr(Cpu*, unsigned char);
static void rr_A(Cpu*);
static void rr_B(Cpu*);
static void rr_C(Cpu*);
static void rr_D(Cpu*);
static void rr_E(Cpu*);
static void rr_H(Cpu*);
static void rr_L(Cpu*);
static void rr_HL_ind(Cpu*);
//------------------- SLA n -------------------
static BYTE sla(Cpu*, unsigned char);
static void sla_A(Cpu*);
static void sla_B(Cpu*);
static void sla_C(Cpu*);
static void sla_D(Cpu*);
static void sla_E(Cpu*);
static void sla_H(Cpu*);
static void sla_L(Cpu*);
static void sla_HL_ind(Cpu*);
//------------------- SRA n -------------------
static BYTE sra(Cpu*, unsigned char);
static void sra_A(Cpu*);
static void sra_B(Cpu*);
static void sra_C(Cpu*);
static void sra_D(Cpu*);
static void sra_E(Cpu*);
static void sra_H(Cpu*);
static void sra_L(Cpu*);
static void sra_HL_ind(Cpu*);
//------------------- SRL n -------------------
static BYTE srl(Cpu*, unsigned char);
static void srl_A(Cpu*);
static void srl_B(Cpu*);
static void srl_C(Cpu*);
static void srl_D(Cpu*);
static void srl_E(Cpu*);
static void srl_H(Cpu*);
static void srl_L(Cpu*);
static void srl_HL_ind(Cpu*);

//________________________________ Bit Opcodes _____________________________

//------------------- BIT b, r -------------------
static void bit_b_r(Cpu*, unsigned char, unsigned char);
static void bit_A_0(Cpu*);
static void bit_A_1(Cpu*);
static void bit_A_2(Cpu*);
static void bit_A_3(Cpu*);
static void bit_A_4(Cpu*);
static void bit_A_5(Cpu*);
static void bit_A_6(Cpu*);
static void bit_A_7(Cpu*);

static void bit_B_0(Cpu*);
static void bit_B_1(Cpu*);
static void bit_B_2(Cpu*);
static void bit_B_3(Cpu*);
static void bit_B_4(Cpu*);
static void bit_B_5(Cpu*);
static void bit_B_6(Cpu*);
static void bit_B_7(Cpu*);

static void bit_C_0(Cpu*);
static void bit_C_1(Cpu*);
static void bit_C_2(Cpu*);
static void bit_C_3(Cpu*);
static void bit_C_4(Cpu*);
static void bit_C_5(Cpu*);
static void bit_C_6(Cpu*);
static void bit_C_7(Cpu*);

static void bit_D_0(Cpu*);
static void bit_D_1(Cpu*);
static void bit_D_2(Cpu*);
static void bit_D_3(Cpu*);
static void bit_D_4(Cpu*);
static void bit_D_5(Cpu*);
static void bit_D_6(Cpu*);
static void bit_D_7(Cpu*);

static void bit_E_0(Cpu*);
static void bit_E_1(Cpu*);
static void bit_E_2(Cpu*);
static void bit_E_3(Cpu*);
static void bit_E_4(Cpu*);
static void bit_E_5(Cpu*);
static void bit_E_6(Cpu*);
static void bit_E_7(Cpu*);

static void bit_H_0(Cpu*);
static void bit_H_1(Cpu*);
static void bit_H_2(Cpu*);
static void bit_H_3(Cpu*);
static void bit_H_4(Cpu*);
static void bit_H_5(Cpu*);
static void bit_H_6(Cpu*);
static void bit_H_7(Cpu*);

static void bit_L(Cpu*);
static void bit_a_HL_ind(Cpu*);
//------------------- SET b, r -------------------
static BYTE set_b_r(Cpu*, unsigned char);
static void set_A(Cpu*);
static void set_B(Cpu*);
static void set_C(Cpu*);
static void set_D(Cpu*);
static void set_E(Cpu*);
static void set_H(Cpu*);
static void set_L(Cpu*);
static void set_a_HL_ind(Cpu*);
//------------------- RES b, r -------------------
static BYTE res_b_r(Cpu*, unsigned char);
static void res_A(Cpu*);
static void res_B(Cpu*);
static void res_C(Cpu*);
static void res_D(Cpu*);
static void res_E(Cpu*);
static void res_H(Cpu*);
static void res_L(Cpu*);
static void res_a_HL_ind(Cpu*);

//________________________________ Jumps _____________________________

//------------------- JP nn -------------------
static void jp(Cpu*);
//------------------- JP cc, nn -------------------
static void jp_nz(Cpu*);
static void jp_z(Cpu*);
static void jp_nc(Cpu*);
static void jp_c(Cpu*);
//------------------- JP (HL) -------------------
static void jp_hl_ind(Cpu*);

//------------------- JR n -------------------
static void jr(Cpu*);
//------------------- JR cc, nn -------------------
static void jr_nz(Cpu*);
static void jr_z(Cpu*);
static void jr_nc(Cpu*);
static void jr_c(Cpu*);

//________________________________ Calls _____________________________

//------------------- JP nn -------------------
static void call(Cpu*);
//------------------- CALL cc, nn -------------------
static void call_nz(Cpu*);
static void call_z(Cpu*);
static void call_nc(Cpu*);
static void call_c(Cpu*);

//________________________________ Restarts _____________________________

//------------------- RST n -------------------
static void rst(Cpu*, unsigned char);
static void rst_0(Cpu*);
static void rst_8(Cpu*);
static void rst_10(Cpu*);
static void rst_18(Cpu*);
static void rst_20(Cpu*);
static void rst_28(Cpu*);
static void rst_30(Cpu*);
static void rst_38(Cpu*);
//------------------- RET -------------------
static void ret(Cpu*);
//------------------- RET cc-------------------
static void ret_nz(Cpu*);
static void ret_z(Cpu*);
static void ret_nc(Cpu*);
static void ret_c(Cpu*);
//------------------- RETI -------------------
static void reti(Cpu*);









#endif