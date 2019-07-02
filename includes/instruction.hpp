#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "utility.hpp"
#include <string>
#include <map>

class Cpu;

struct instruction {
    std::string name;           //name of the instruction
    BYTE cycles;                //clock cycles needed to be executed
    void (*function)(Cpu*);     //pointer to the function to be emulated

    //constructor
    instruction(std::string, BYTE, void(*)(Cpu*));
};

void init(std::map<unsigned char, instruction>&);
void initCBPrefix(std::map<unsigned char, instruction>&);


//________________________________ 8/bit Arithmetic_____________________________

//------------------- NOT_DEFINED -------------------
static void not_defined(Cpu*);

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
static void sbc_A_n(Cpu*);
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
static BYTE load_nn_n(Cpu*);
static void load_A_n(Cpu*);
static void load_B_n(Cpu*);
static void load_C_n(Cpu*);
static void load_D_n(Cpu*);
static void load_E_n(Cpu*);
static void load_H_n(Cpu*);
static void load_L_n(Cpu*);

//------------------- LOAD r1, r2 -------------------
static void load_A_A(Cpu*);
static void load_A_B(Cpu*);
static void load_A_C(Cpu*);
static void load_A_D(Cpu*);
static void load_A_E(Cpu*);
static void load_A_H(Cpu*);
static void load_A_L(Cpu*);
static void load_A_HL_ind(Cpu*);

static void load_B_A(Cpu*);
static void load_B_B(Cpu*);
static void load_B_C(Cpu*);
static void load_B_D(Cpu*);
static void load_B_E(Cpu*);
static void load_B_H(Cpu*);
static void load_B_L(Cpu*);
static void load_B_HL_ind(Cpu*);

static void load_C_A(Cpu*);
static void load_C_B(Cpu*);
static void load_C_C(Cpu*);
static void load_C_D(Cpu*);
static void load_C_E(Cpu*);
static void load_C_H(Cpu*);
static void load_C_L(Cpu*);
static void load_C_HL_ind(Cpu*);

static void load_D_A(Cpu*);
static void load_D_B(Cpu*);
static void load_D_C(Cpu*);
static void load_D_D(Cpu*);
static void load_D_E(Cpu*);
static void load_D_H(Cpu*);
static void load_D_L(Cpu*);
static void load_D_HL_ind(Cpu*);

static void load_E_A(Cpu*);
static void load_E_B(Cpu*);
static void load_E_C(Cpu*);
static void load_E_D(Cpu*);
static void load_E_E(Cpu*);
static void load_E_H(Cpu*);
static void load_E_L(Cpu*);
static void load_E_HL_ind(Cpu*);

static void load_H_A(Cpu*);
static void load_H_B(Cpu*);
static void load_H_C(Cpu*);
static void load_H_D(Cpu*);
static void load_H_E(Cpu*);
static void load_H_H(Cpu*);
static void load_H_L(Cpu*);
static void load_H_HL_ind(Cpu*);

static void load_L_A(Cpu*);
static void load_L_B(Cpu*);
static void load_L_C(Cpu*);
static void load_L_D(Cpu*);
static void load_L_E(Cpu*);
static void load_L_H(Cpu*);
static void load_L_L(Cpu*);
static void load_L_HL_ind(Cpu*);

static void load_HL_ind_x(Cpu*, unsigned char);
static void load_HL_ind_A(Cpu*);
static void load_HL_ind_B(Cpu*);
static void load_HL_ind_C(Cpu*);
static void load_HL_ind_D(Cpu*);
static void load_HL_ind_E(Cpu*);
static void load_HL_ind_H(Cpu*);
static void load_HL_ind_L(Cpu*);
static void load_HL_ind_n(Cpu*);

//------------------- LOAD A, (nn) -------------------
static void load_A_x_ind(Cpu*, unsigned short);
static void load_A_BC_ind(Cpu*);
static void load_A_DE_ind(Cpu*);
//static void load_A_HL_ind(Cpu*);
static void load_A_nn_ind(Cpu*);


//------------------- LOAD n, A -------------------
static void load_xx_ind_A(Cpu*, unsigned char);
static void load_BC_ind_A(Cpu*);
static void load_DE_ind_A(Cpu*);
//static void load_HL_ind_A(Cpu*);
static void load_nn_ind_A(Cpu*);

//------------------- LOAD A, (C) -------------------
static void load_A_C_ind(Cpu*);
//------------------- LOAD (C), A -------------------
static void load_C_ind_A(Cpu*);

/* //------------------- LOAD A, (HLD) -------------------
static void load_A_HLD_ind(Cpu*);
//------------------- LOAD A, (HL-) -------------------
static void load_A_HL__ind(Cpu*); */
//------------------- LOADD A, (HL) -------------------
static void loadd_A_HL_ind(Cpu*);

/* //------------------- LOAD (HLD), A -------------------
static void load_HLD_ind_A(Cpu*);
//------------------- LOAD A(HL-), A -------------------
static void loadHL__ind_A(Cpu*); */
//------------------- LOADD (HL), A -------------------
static void loadd_HL_ind_A(Cpu*);

//------------------- LOADI A, (HL) -------------------
static void loadi_A_HL_ind(Cpu*);
//------------------- LOADI (HL), A -------------------
static void loadi_HL_ind_A(Cpu*);

//------------------- LOADH (n), A -------------------
static void loadh_n_ind_A(Cpu*);
//------------------- LOADH A, (n) -------------------
static void loadh_A_n_ind(Cpu*);

//________________________________ 16-bit Load _____________________________

//------------------- LOAD n, nn -------------------
static WORD load_n_nn(Cpu*);
static void load_BC_nn(Cpu*);
static void load_DE_nn(Cpu*);
static void load_HL_nn(Cpu*);
static void load_SP_nn(Cpu*);
//------------------- LOAD SP, HL -------------------
static void load_SP_HL(Cpu*);
//------------------- LOADHL SP, n -------------------
static void loadhl_SP_n(Cpu*);
//------------------- LOAD nn, SP -------------------
static void load_nn_SP(Cpu*);
//------------------- PUSH nn -------------------
static void push_nn(Cpu*, unsigned short);
static void push_AF(Cpu*);
static void push_BC(Cpu*);
static void push_DE(Cpu*);
static void push_HL(Cpu*);
//------------------- POP nn -------------------
static WORD pop_nn(Cpu*);
static void pop_AF(Cpu*);
static void pop_BC(Cpu*);
static void pop_DE(Cpu*);
static void pop_HL(Cpu*);

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
static void swap_HL_ind(Cpu*);
//------------------- DAA -------------------
static void daa(Cpu*);
//------------------- CPL n -------------------
static void cpl(Cpu*);
//------------------- CCF -------------------
static void ccf(Cpu*);
//------------------- SCF -------------------
static void scf(Cpu*);
//------------------- NOP -------------------
static void nop(Cpu*);
//------------------- HALT -------------------
static void halt(Cpu*);
//------------------- STOP -------------------
static void stop(Cpu*);
//------------------- DI -------------------
static void di(Cpu*);
//------------------- EI -------------------
static void ei(Cpu*);

//________________________________ Rotates and shifts _____________________________

//------------------- RLC n -------------------
static BYTE rlc(Cpu*, unsigned char);
static BYTE rlc_n(Cpu*, unsigned char);
static void rlca(Cpu*);


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
static BYTE rl_n(Cpu*, unsigned char);
static void rla(Cpu*);

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
static BYTE rrc_n(Cpu*, unsigned char);
static void rrca(Cpu*);


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
static BYTE rr_n(Cpu*, unsigned char);
static void rra(Cpu*);


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

//------------------- BIT -------------------
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

static void bit_L_0(Cpu*);
static void bit_L_1(Cpu*);
static void bit_L_2(Cpu*);
static void bit_L_3(Cpu*);
static void bit_L_4(Cpu*);
static void bit_L_5(Cpu*);
static void bit_L_6(Cpu*);
static void bit_L_7(Cpu*);

static void bit_HL_ind_0(Cpu*);
static void bit_HL_ind_1(Cpu*);
static void bit_HL_ind_2(Cpu*);
static void bit_HL_ind_3(Cpu*);
static void bit_HL_ind_4(Cpu*);
static void bit_HL_ind_5(Cpu*);
static void bit_HL_ind_6(Cpu*);
static void bit_HL_ind_7(Cpu*);

//------------------- SET -------------------
static BYTE set_b_r(Cpu*, unsigned char);
static void set_A_0(Cpu*);
static void set_A_1(Cpu*);
static void set_A_2(Cpu*);
static void set_A_3(Cpu*);
static void set_A_4(Cpu*);
static void set_A_5(Cpu*);
static void set_A_6(Cpu*);
static void set_A_7(Cpu*);

static void set_B_0(Cpu*);
static void set_B_1(Cpu*);
static void set_B_2(Cpu*);
static void set_B_3(Cpu*);
static void set_B_4(Cpu*);
static void set_B_5(Cpu*);
static void set_B_6(Cpu*);
static void set_B_7(Cpu*);

static void set_C_0(Cpu*);
static void set_C_1(Cpu*);
static void set_C_2(Cpu*);
static void set_C_3(Cpu*);
static void set_C_4(Cpu*);
static void set_C_5(Cpu*);
static void set_C_6(Cpu*);
static void set_C_7(Cpu*);

static void set_D_0(Cpu*);
static void set_D_1(Cpu*);
static void set_D_2(Cpu*);
static void set_D_3(Cpu*);
static void set_D_4(Cpu*);
static void set_D_5(Cpu*);
static void set_D_6(Cpu*);
static void set_D_7(Cpu*);

static void set_E_0(Cpu*);
static void set_E_1(Cpu*);
static void set_E_2(Cpu*);
static void set_E_3(Cpu*);
static void set_E_4(Cpu*);
static void set_E_5(Cpu*);
static void set_E_6(Cpu*);
static void set_E_7(Cpu*);

static void set_H_0(Cpu*);
static void set_H_1(Cpu*);
static void set_H_2(Cpu*);
static void set_H_3(Cpu*);
static void set_H_4(Cpu*);
static void set_H_5(Cpu*);
static void set_H_6(Cpu*);
static void set_H_7(Cpu*);

static void set_L_0(Cpu*);
static void set_L_1(Cpu*);
static void set_L_2(Cpu*);
static void set_L_3(Cpu*);
static void set_L_4(Cpu*);
static void set_L_5(Cpu*);
static void set_L_6(Cpu*);
static void set_L_7(Cpu*);

static void set_HL_ind_0(Cpu*);
static void set_HL_ind_1(Cpu*);
static void set_HL_ind_2(Cpu*);
static void set_HL_ind_3(Cpu*);
static void set_HL_ind_4(Cpu*);
static void set_HL_ind_5(Cpu*);
static void set_HL_ind_6(Cpu*);
static void set_HL_ind_7(Cpu*);

//------------------- RES -------------------
static BYTE res_b_r(Cpu*, unsigned char);
static void res_A_0(Cpu*);
static void res_A_1(Cpu*);
static void res_A_2(Cpu*);
static void res_A_3(Cpu*);
static void res_A_4(Cpu*);
static void res_A_5(Cpu*);
static void res_A_6(Cpu*);
static void res_A_7(Cpu*);

static void res_B_0(Cpu*);
static void res_B_1(Cpu*);
static void res_B_2(Cpu*);
static void res_B_3(Cpu*);
static void res_B_4(Cpu*);
static void res_B_5(Cpu*);
static void res_B_6(Cpu*);
static void res_B_7(Cpu*);

static void res_C_0(Cpu*);
static void res_C_1(Cpu*);
static void res_C_2(Cpu*);
static void res_C_3(Cpu*);
static void res_C_4(Cpu*);
static void res_C_5(Cpu*);
static void res_C_6(Cpu*);
static void res_C_7(Cpu*);

static void res_D_0(Cpu*);
static void res_D_1(Cpu*);
static void res_D_2(Cpu*);
static void res_D_3(Cpu*);
static void res_D_4(Cpu*);
static void res_D_5(Cpu*);
static void res_D_6(Cpu*);
static void res_D_7(Cpu*);

static void res_E_0(Cpu*);
static void res_E_1(Cpu*);
static void res_E_2(Cpu*);
static void res_E_3(Cpu*);
static void res_E_4(Cpu*);
static void res_E_5(Cpu*);
static void res_E_6(Cpu*);
static void res_E_7(Cpu*);

static void res_H_0(Cpu*);
static void res_H_1(Cpu*);
static void res_H_2(Cpu*);
static void res_H_3(Cpu*);
static void res_H_4(Cpu*);
static void res_H_5(Cpu*);
static void res_H_6(Cpu*);
static void res_H_7(Cpu*);

static void res_L_0(Cpu*);
static void res_L_1(Cpu*);
static void res_L_2(Cpu*);
static void res_L_3(Cpu*);
static void res_L_4(Cpu*);
static void res_L_5(Cpu*);
static void res_L_6(Cpu*);
static void res_L_7(Cpu*);

static void res_HL_ind_0(Cpu*);
static void res_HL_ind_1(Cpu*);
static void res_HL_ind_2(Cpu*);
static void res_HL_ind_3(Cpu*);
static void res_HL_ind_4(Cpu*);
static void res_HL_ind_5(Cpu*);
static void res_HL_ind_6(Cpu*);
static void res_HL_ind_7(Cpu*);

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