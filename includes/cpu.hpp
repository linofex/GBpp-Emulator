#ifndef CPU_H
#define CPU_H


#include <string>
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
    void* function;
};

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
#define resetFlag(n) (regAF.high &= n)
#define clearFlag(n) (regAF.high &= ~n)

#include <map>
using namespace std;

class Cpu {
    
    private:

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
        
        void fillInstructions(string, unsigned char, void*);

        bool checkCartridge(void);

        BYTE fetch(void);
        void* decode(BYTE);
        void execute(void*);

    public:
        Cpu(void);
        ~Cpu(void);

        //instruction makeInstructions(std::string, int, int, void*);
        void addInstructions(void);


        void reset(void);
        void step(void);

        //--------------------- 8-bit arithmetic ---------------------
        void adc(unsigned char);
        void adc_A_A(void);
        void adc_A_B(void);
        void adc_A_C(void);
        void adc_A_D(void);
        void adc_A_E(void);
        void adc_A_H(void);
        void adc_A_L(void);
        void adc_A_HL_ind(void);
        void adc_A_n(unsigned char);

        void add(unsigned char);
        void add_A_A(void);
        void add_A_B(void);
        void add_A_C(void);
        void add_A_D(void);
        void add_A_E(void);
        void add_A_H(void);
        void add_A_L(void);
        void add_A_HL_ind(void);
        void add_A_n(unsigned char);

        void sub(unsigned char);
        void sub_A_A(void);
        void sub_A_B(void);
        void sub_A_C(void);
        void sub_A_D(void);
        void sub_A_E(void);
        void sub_A_H(void);
        void sub_A_L(void);
        void sub_A_HL_ind(void);
        void sub_A_n(unsigned char);

        void sbc(unsigned char);
        void sbc_A_A(void);
        void sbc_A_B(void);
        void sbc_A_C(void);
        void sbc_A_D(void);
        void sbc_A_E(void);
        void sbc_A_H(void);
        void sbc_A_L(void);
        void sbc_A_HL_ind(void);
        //void sbc_A_n(unsigned char n);

        void and_(unsigned char);
        void and_A_A(void);
        void and_A_B(void);
        void and_A_C(void);
        void and_A_D(void);
        void and_A_E(void);
        void and_A_H(void);
        void and_A_L(void);
        void and_A_HL_ind(void);
        void and_A_n(unsigned char);

        void or_(unsigned char);
        void or_A_A(void);
        void or_A_B(void);
        void or_A_C(void);
        void or_A_D(void);
        void or_A_E(void);
        void or_A_H(void);
        void or_A_L(void);
        void or_A_HL_ind(void);
        void or_A_n(unsigned char);

        void xor_(unsigned char);
        void xor_A_A(void);
        void xor_A_B(void);
        void xor_A_C(void);
        void xor_A_D(void);
        void xor_A_E(void);
        void xor_A_H(void);
        void xor_A_L(void);
        void xor_A_HL_ind(void);
        void xor_A_n(unsigned char);

        void cp(unsigned char);
        void cp_A_A(void);
        void cp_A_B(void);
        void cp_A_C(void);
        void cp_A_D(void);
        void cp_A_E(void);
        void cp_A_H(void);
        void cp_A_L(void);
        void cp_A_HL_ind(void);
        void cp_A_n(unsigned char);

        void inc(unsigned char*);
        void inc_A(void);
        void inc_B(void);
        void inc_C(void);
        void inc_D(void);
        void inc_E(void);
        void inc_H(void);
        void inc_L(void);
        void inc_HL_ind(void);

        void dec(unsigned char*);
        void dec_A(void);
        void dec_B(void);
        void dec_C(void);
        void dec_D(void);
        void dec_E(void);
        void dec_H(void);
        void dec_L(void);
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

#endif
