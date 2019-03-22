#ifndef CPU_H
#define CPU_H

#include "memory.hpp"
#include <string>
#include <vector>

typedef unsigned char BYTE;        //8 bit
typedef unsigned short WORD;       //16 bits

//regAF.reg -> AF, regAF.high -> A, regAF.low -> F
union REGISTER {
    WORD reg;
    struct {
        BYTE low;
        BYTE high;
    };
};

struct instruction {
    std::string name;
    int cycles;
    int paramNum;
    void *function;
};

#define internalROMSize 48
#define internalROMName "comparison.txt"

//flag register F (only 4 bit are used) |Z|N|H|C|x|x|x|x|
#define flagZ 7
#define flagN 6
#define flagH 5
#define flagC 4

//functions on flags register
#define isFlagZero(void)(regAF.high & (1 << flagZ))
#define isFlagNeg(void) (regAF.high & (1 << flagN))
#define isFlagHalfCarry(void) (regAF.high & (1 << flagH))
#define isFlagCarry(void) (regAF.high & (1 << flagC))

#define setFlag(n) (regAF.high |= n)
#define resetFlag(n) (regAF.high &= ~n)
//#define clearFlag(n) (regAF.high &= ~n)

#include <map>
namespace GBemulator {

    class Cpu {
        
        private:
            //pointer to other classes instances
            Memory* mem;

            //special registers of 16 bits
            WORD pc;    //program counter
            WORD sp;    //stack pointer

            //internal registers of 16 bits
            REGISTER regAF;
            REGISTER regBC;
            REGISTER regDE;
            REGISTER regHL;
        
            //timer
            float timer;

            //map for the instructions
            std::map<unsigned char, instruction> instrMap;           
            void fillInstructions(void);
            instruction addInstruction(std::string, int, int, void*);

            std::vector<BYTE> intROM;
            bool checkCartridge(void);
            void loadInternalROM(void);

            BYTE fetch(void);
            instruction decode(BYTE);
            void execute(instruction);

        public:
            //Cpu(void);
            Cpu(const Memory&);
            ~Cpu(void);
            
            void reset(void);
            void step(void);

            inline WORD getSp(void) const {return sp;}
            inline WORD getPc(void) const {return pc;}
            inline void setPc(const WORD t_pc) {pc = t_pc;}
            inline void decreaseSp(void) {sp--;}
            inline void increaseSp(void) {sp++;}
            

            //--------------------- 8-bit arithmetic ---------------------
            void adc(unsigned char);
            inline void adc_A_A(void) {adc(regAF.high);};
            inline void adc_A_B(void) {adc(regBC.high);};
            inline void adc_A_C(void) {adc(regBC.low);};
            inline void adc_A_D(void) {adc(regDE.high);};
            inline void adc_A_E(void) {adc(regDE.low);};
            inline void adc_A_H(void) {adc(regHL.high);};
            inline void adc_A_L(void) {adc(regHL.low);};
            void adc_A_HL_ind(void);
            void adc_A_n(unsigned char);

            void add(unsigned char);
            inline void add_A_A(void) {add(regAF.high);};
            inline void add_A_B(void) {add(regBC.high);};
            inline void add_A_C(void) {add(regBC.low);};
            inline void add_A_D(void) {add(regDE.high);};
            inline void add_A_E(void) {add(regDE.low);};
            inline void add_A_H(void) {add(regHL.high);};
            inline void add_A_L(void) {add(regHL.low);};
            void add_A_HL_ind(void);
            void add_A_n(unsigned char);

            void sub(unsigned char);
            inline void sub_A_A(void) {sub(regAF.high);};
            inline void sub_A_B(void) {sub(regBC.high);};
            inline void sub_A_C(void) {sub(regBC.low);};
            inline void sub_A_D(void) {sub(regDE.high);};
            inline void sub_A_E(void) {sub(regDE.low);};
            inline void sub_A_H(void) {sub(regHL.high);};
            inline void sub_A_L(void) {sub(regHL.low);};
            void sub_A_HL_ind(void);
            void sub_A_n(unsigned char);

            void sbc(unsigned char);
            inline void sbc_A_A(void) {sbc(regAF.high);};
            inline void sbc_A_B(void) {sbc(regBC.high);};
            inline void sbc_A_C(void) {sbc(regBC.low);};
            inline void sbc_A_D(void) {sbc(regDE.high);};
            inline void sbc_A_E(void) {sbc(regDE.low);};
            inline void sbc_A_H(void) {sbc(regHL.high);};
            inline void sbc_A_L(void) {sbc(regHL.low);};
            void sbc_A_HL_ind(void);
            //void sbc_A_n(unsigned char n);

            void and_(unsigned char);
            inline void and_A_A(void) {and_(regAF.high);};
            inline void and_A_B(void) {and_(regBC.high);};
            inline void and_A_C(void) {and_(regBC.low);};
            inline void and_A_D(void) {and_(regDE.high);};
            inline void and_A_E(void) {and_(regDE.low);};
            inline void and_A_H(void) {and_(regHL.high);};
            inline void and_A_L(void) {and_(regHL.low);};
            void and_A_HL_ind(void);
            void and_A_n(unsigned char);

            void or_(unsigned char);
            inline void or_A_A(void) {or_(regAF.high);};
            inline void or_A_B(void) {or_(regBC.high);};
            inline void or_A_C(void) {or_(regBC.low);};
            inline void or_A_D(void) {or_(regDE.high);};
            inline void or_A_E(void) {or_(regDE.low);};
            inline void or_A_H(void) {or_(regHL.high);};
            inline void or_A_L(void) {or_(regHL.low);};
            void or_A_HL_ind(void);
            void or_A_n(unsigned char);

            void xor_(unsigned char);
            inline void xor_A_A(void) {xor_(regAF.high);};
            inline void xor_A_B(void) {xor_(regBC.high);};
            inline void xor_A_C(void) {xor_(regBC.low);};
            inline void xor_A_D(void) {xor_(regDE.high);};
            inline void xor_A_E(void) {xor_(regDE.low);};
            inline void xor_A_H(void) {xor_(regHL.high);};
            inline void xor_A_L(void) {xor_(regHL.low);};
            void xor_A_HL_ind(void);
            void xor_A_n(unsigned char);

            void cp(unsigned char);
            inline void cp_A_A(void) {cp(regAF.high);};
            inline void cp_A_B(void) {cp(regBC.high);};
            inline void cp_A_C(void) {cp(regBC.low);};
            inline void cp_A_D(void) {cp(regDE.high);};
            inline void cp_A_E(void) {cp(regDE.low);};
            inline void cp_A_H(void) {cp(regHL.high);};
            inline void cp_A_L(void) {cp(regHL.low);};
            void cp_A_HL_ind(void);
            void cp_A_n(unsigned char);

            void inc(unsigned char*);
            inline void inc_A(void) {inc(&regAF.high);};
            inline void inc_B(void) {inc(&regBC.high);};
            inline void inc_C(void) {inc(&regBC.low);};
            inline void inc_D(void) {inc(&regDE.high);};
            inline void inc_E(void) {inc(&regDE.low);};
            inline void inc_H(void) {inc(&regHL.high);};
            inline void inc_L(void) {inc(&regHL.low);}
            /* void inc_A(void);
            void inc_B(void);
            void inc_C(void);
            void inc_D(void);
            void inc_E(void);
            void inc_H(void);
            void inc_L(void); */
            void inc_HL_ind(void);

            void dec(unsigned char*);
            inline void dec_A_A(void) {dec(&regAF.high);};
            inline void dec_A_B(void) {dec(&regBC.high);};
            inline void dec_A_C(void) {dec(&regBC.low);};
            inline void dec_A_D(void) {dec(&regDE.high);};
            inline void dec_A_E(void) {dec(&regDE.low);};
            inline void dec_A_H(void) {dec(&regHL.high);};
            inline void dec_A_L(void) {dec(&regHL.low);};
            /*void dec_A(void);
            void dec_B(void);
            void dec_C(void);
            void dec_D(void);
            void dec_E(void);
            void dec_H(void);
            void dec_L(void);*/
            void dec_HL_ind(void);

            //--------------------- 16-bit arithmetic ---------------------
            void addWord(unsigned short);
            void add_HL_BC(void);
            void add_HL_DE(void);
            void add_HL_HL(void);
            void add_HL_SP(void);

            void add_SP_n(signed char);

            //void incWord(unsigned char*);
            void inc_BC(void);
            void inc_DE(void);
            void inc_HL(void);
            void inc_SP(void);

            //void decWord(unsigned char*);
            void dec_BC(void);
            void dec_DE(void);
            void dec_HL(void);
            void dec_SP(void);


    };
};
#endif
