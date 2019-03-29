#ifndef CPU_H
#define CPU_H

#include "memory.hpp"
#include "instruction.hpp"
#include <string>
#include <vector>
#include <chrono>
#include <ctime>

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

//#define internalROMSize 48
//#define internalROMName "comparison.txt"

//clock
#define CLOCK 4194304
#define TARGETPERIOD 0.000238418     //1000/(4194304)
#define HOSTPERIOD 1/(25*10^9)      //0.4 ns

//locations for the timers
#define DIVIDER 0xFF04
#define TIMA 0xFF05
#define TMA 0xFF06
#define TMC 0xFF07

//flag register F (only 4 bit are used) |Z|N|H|C|x|x|x|x|
#define flagZ 7
#define flagN 6
#define flagH 5
#define flagC 4

//functions on flags register
/*#define isFlagZero(void)(regAF.high & (1 << flagZ))
#define isFlagNeg(void) (regAF.high & (1 << flagN))
#define isFlagHalfCarry(void) (regAF.high & (1 << flagH))
#define isFlagCarry(void) (regAF.high & (1 << flagC))

#define setFlag(n) (regAF.high |= n)
#define resetFlag(n) (regAF.high &= ~n)
//#define clearFlag(n) (regAF.high &= ~n)*/

#include <map>

class Cpu {
    
    private:
        //useful pointers
        Memory* mem;

        //special registers of 16 bits
        WORD pc;    //program counter
        WORD sp;    //stack pointer

        //internal registers of 16 bits
        REGISTER regAF;
        REGISTER regBC;
        REGISTER regDE;
        REGISTER regHL;
    
        //clock cycles passed
        WORD clockCycles;

        //timer
        WORD timerCounter;
        WORD dividerCounter;

        std::chrono::time_point<std::chrono::system_clock> hostOldTime;
        //std::chrono::time_point<std::chrono::system_clock> targetOldTime;
        unsigned int targetOldTime;

        //map for the instructions
        std::map<unsigned char, struct instruction> instrSet;
        void initInstructions(void);
        std::map<unsigned char, struct instruction> instrSetCBPrefix;

        //interrupt master enable
        bool intMasterEnable;       //an interrupt can only be served IFF this is TRUE

        //execution functions
        BYTE fetch(void);
        struct instruction decode(BYTE);
        void execute(instruction);

        //timing functions
        void stepTimer(int);
        void stepDivider(int);
        void updateTimers(int);
        void setTimer(void);
        inline WORD getTimer(){return timerCounter;};
        void sync(void);
        bool isTimerOn(void);


    public:
        Cpu(void);
        Cpu(Memory*);
        ~Cpu(void);
        
        void reset(void);
        void step(void);

        inline bool isIntMasterEnable(void) const {return intMasterEnable;}
        void setIntMasterEnable(void) {intMasterEnable = true;}
        void resetIntMasterEnable(void) {intMasterEnable = false;}

        void pushWord(WORD);
        WORD popWord(void);
        void push(BYTE);
        BYTE popByte(void);

        inline BYTE getA(void) const {return regAF.high;}
        inline BYTE getB(void) const {return regBC.high;}
        inline BYTE getC(void) const {return regBC.low;}
        inline BYTE getD(void) const {return regDE.high;}
        inline BYTE getE(void) const {return regDE.low;}
        inline BYTE getF(void) const {return regAF.low;}
        inline BYTE getH(void) const {return regHL.high;}
        inline BYTE getL(void) const {return regHL.low;}
        inline WORD getHL(void) const {return regHL.reg;}
        inline WORD getAF(void) const {return regAF.reg;}
        inline WORD getBC(void) const {return regBC.reg;}
        inline WORD getDE(void) const {return regDE.reg;}

        inline void setA(const BYTE t_a) {regAF.high = t_a;}
        inline void setB(const BYTE t_b) {regBC.high = t_b;}
        inline void setC(const BYTE t_c) {regBC.low = t_c;}
        inline void setD(const BYTE t_d) {regDE.high = t_d;}
        inline void setE(const BYTE t_e) {regDE.low = t_e;}
        inline void setH(const BYTE t_h) {regHL.high = t_h;}
        inline void setL(const BYTE t_l) {regHL.low = t_l;}
        inline void setHL(const WORD t_hl) {regHL.reg = t_hl;}
        inline void setAF(const WORD t_af) {regAF.reg = t_af;}
        inline void setBC(const WORD t_bc) {regBC.reg = t_bc;}
        inline void setDE(const WORD t_de) {regDE.reg = t_de;}
        inline void setSP(const WORD t_sp) {sp = t_sp;}

        inline BYTE isFlagZero(void) {return regAF.low & (1 << flagZ);}
        inline BYTE isFlagNeg(void) {return regAF.low & (1 << flagN);}
        inline BYTE isFlagHalfCarry(void) {return regAF.low & (1 << flagH);}
        inline BYTE isFlagCarry(void) {return regAF.low & (1 << flagC);}

        inline void setFlag(const BYTE n) {regAF.high |= n;}
        inline void resetFlag(const BYTE n) {regAF.high &= ~n;}

        inline BYTE readByte(WORD t_addr) {return mem->readByte(t_addr);}
        inline void writeByte(WORD t_addr, BYTE t_val) {mem->writeByte(t_addr, t_val);}
        inline WORD readWord(WORD t_addr) {return mem->readWord(t_addr);}
        inline void writeWord(WORD t_addr, BYTE t_val) {mem->writeWord(t_addr, t_val);}

        inline WORD getSP(void) const {return sp;}
        inline WORD getPC(void) const {return pc;}
        inline void setPC(const WORD t_pc) {pc = t_pc;}
        
        inline void decPC(void) {pc--;}
        inline void incPC(void) {pc++;}
        inline void decSP(void) {sp--;}
        inline void incSP(void) {sp++;}

        struct instruction getInstrSetAt(BYTE);
        struct instruction getInstrSetCBPrefixAt(BYTE);
        


        /* //--------------------- 16-bit arithmetic ---------------------
        void addWord(unsigned short);
        //void add_HL_BC(void);
        void add_HL_DE(void);
        void add_HL_HL(void);
        void add_HL_SP(void);

        void add_SP_n(signed char); */

        //void incWord(unsigned char*);
        //void inc_BC(void);
        //void inc_DE(void);
        //void inc_HL(void);
        //void inc_SP(void);

        //void decWord(unsigned char*);
        //void dec_BC(void);
        // dec_DE(void);
        //void dec_HL(void);
        //void dec_SP(void);


};

#endif
