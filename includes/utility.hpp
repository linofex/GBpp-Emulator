#ifndef UTIL_H
#define UTIL_H

typedef unsigned char BYTE; // 8bit
typedef unsigned short WORD; // 16bit

// interrupt types
#define VBLANK  0x01
#define LCD     0x02
#define TIMER   0x04
#define JOYPAD  0x10 

//flag register F (only 4 bit are used) |Z|N|H|C|x|x|x|x|
#define FLAG_Z 0x80 // bit 7
#define FLAG_N 0x40 // bit 6
#define FLAG_H 0x20 // bit 5
#define FLAG_C 0x10 // bit 4

//regAF.reg -> AF, regAF.high -> A, regAF.low -> F
union REGISTER {
    WORD reg;
    struct {
        BYTE low;
        BYTE high;
    };
};

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

// LCD Registers
#define LCDCONTROL  0xFF40
#define LCDSTATUS   0xFF41
#define LCDLY       0xFF44
#define LCDLYC      0xFF45

// LCD modes
#define MODE0 0x00
#define MODE1 0x01
#define MODE2 0x10
#define MODE3 0x11

// DMA
#define DMA 0xFF46

// Screen Dimension
#define SCREEN_WIDTH    160
#define SCREEN_HEIGHT   144

// Joypad status variables
#define RIGHT   0
#define LEFT    1
#define UP      2
#define DOWN    3
#define A       4
#define B       5
#define SELECT  6
#define START   7
#define BUTTON  1 << 5
#define DIRECTION  1 << 4

#define PRESSION_DURATION 200

#endif