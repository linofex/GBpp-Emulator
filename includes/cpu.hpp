#ifndef CPU_H
#define CPU_H

#include "utility.hpp"
#include "memory.hpp"
#include "instruction.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <set>
#include <map>

class Cpu {
    
    private:
        //useful pointers
        Memory* memory;
        //special registers of 16 bits
        WORD pc;    //program counter
        WORD sp;    //stack pointer

        //internal registers of 16 bits
        REGISTER regAF;
        REGISTER regBC;
        REGISTER regDE;
        REGISTER regHL;
        
        unsigned long clockCycles;
    
        
        std::map<unsigned char, struct instruction> instrSet;           //map for the instructions
        std::map<unsigned char, struct instruction> instrSetCBPrefix;   //map for the extended instructions
        void initInstructions(void);      //creates the two maps

        //interrupt master enable
        bool intMasterEnable; //an interrupt can only be served IFF this is TRUE
        
        BYTE opcode;
        BYTE lastOpcode;
        
        bool halt; //use to halt the CPU after HALT instruction
        bool stop; //use to stop the CPU after STOP instruction

        //CPU step functions
        BYTE fetch(void);
        struct instruction decode(BYTE);
        BYTE execute(instruction);
       
   
    public:
        void printCpuState(void);

        Cpu(void);
        Cpu(Memory*);
        ~Cpu(void);
        
        void reset(void);
        BYTE step(void);
        void stepDebug(std::set<BYTE>*);
        

        inline bool isIntMasterEnable(void) const {return intMasterEnable;}
        inline void setIntMasterEnable(void) {intMasterEnable = true;}
        inline void resetIntMasterEnable(void) {intMasterEnable = false;}

        inline bool isLastOpcode(BYTE t_opcode) const {return lastOpcode == t_opcode;}
        inline void setLastOpcode(BYTE t_opcode) {lastOpcode = t_opcode;}
        
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
        inline void setAF(const WORD t_af) {regAF.reg = t_af & 0xFFF0;}
        inline void setBC(const WORD t_bc) {regBC.reg = t_bc;}
        inline void setDE(const WORD t_de) {regDE.reg = t_de;}
        inline void setHL(const WORD t_hl) {regHL.reg = t_hl;}
        inline void setSP(const WORD t_sp) {sp = t_sp;}

        inline BYTE isFLAG_Zero(void) {return (regAF.low & FLAG_Z);}
        inline BYTE isFLAG_Neg(void) {return (regAF.low &  FLAG_N);}
        inline BYTE isFLAG_HalfCarry(void) {return (regAF.low & FLAG_H);}
        inline BYTE isFLAG_Carry(void) {return (regAF.low &  FLAG_C);}

        inline void setFlag(const BYTE n) {regAF.low |= n;}
        inline void resetFlag(const BYTE n) {regAF.low &= ~n;}

        inline BYTE readByte(WORD t_addr) {return memory->readByte(t_addr);}
        inline void writeByte(WORD t_addr, BYTE t_val) {memory->writeByte(t_addr, t_val);}
        inline WORD readWord(WORD t_addr) {return memory->readWord(t_addr);}
        inline void writeWord(WORD t_addr, WORD t_val) {memory->writeWord(t_addr, t_val);}

        inline WORD getSP(void) const {return sp;}
        inline WORD getPC(void) const {return pc;}
        inline void setPC(const WORD t_pc) {pc = t_pc;}
        
        inline void decPC(void) {pc--;}
        inline void incPC(void) {pc++;}
        inline void decSP(void) {sp--;}
        inline void incSP(void) {sp++;}

        struct instruction getInstrSetAt(BYTE);
        struct instruction getInstrSetCBPrefixAt(BYTE);

        inline void setStop(){stop = true;}
        inline void setHalt(){halt = true;}
        inline void resetStop(){stop = false;}
        inline void resethalt(){halt = false;}
        inline bool isHalted() const {return halt;}
        inline bool isStopped() const {return stop;}

        inline unsigned long getClockCycles() const {return clockCycles;}
        inline void addClockCycles(int t_clock){clockCycles += t_clock;}
        inline void resetClockCycles(void){clockCycles = 0;}
        
};

#endif
