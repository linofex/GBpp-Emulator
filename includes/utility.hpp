#ifndef UTIL_H
#define UTIL_H

typedef unsigned char BYTE; // 8bit
typedef unsigned short WORD; // 16bit

// interrupt types
#define VBLANK  0x01
#define LCD     0x02
#define TIMER   0x04
#define JOYPAD  0x10  

// interrupt routines addresses
#define VBLANK_ADD  0x40
#define LCD_ADD     0x48
#define TIMER_ADD   0X50
#define JOYPAD_ADD  0x60

// gameboy emulation
#define CLOCK 4194304
#define TARGETPERIOD 0.000238418     //1000/(4194304)
#define HOSTPERIOD 1/(25*10^9)      //0.4 ns

//locations for the timers
#define DIVIDER 0xFF04
#define TIMA 0xFF05
#define TMA 0xFF06
#define TMC 0xFF07

//#if defined MEMORY_H
    #define KB 0x400    // 1024B
    #define IER_ADD 0xFFFF  // Interrupt Enable Register address
    #define IRR_ADD 0xFF0F  // Interrupt Request Register address
//#endif



#endif