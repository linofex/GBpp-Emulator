#ifndef UTIL_H
#define UTIL_H

typedef unsigned char BYTE; // 8bit
typedef unsigned short WORD; // 16bit

#define VBLANK  0x01
#define LCD     0x02
#define TIMER   0x04
#define JOYPAD  0x10  

#define VBLANK_ADD  0x40
#define LCD_ADD     0x48
#define TIMER_ADD   0X50
#define JOYPAD_ADD  0x60

//#if defined MEMORY_H
    #define KB 0x400    // 1024B
    #define IER_ADD 0xFFFF  // Interrupt Enable Register address
    #define IRR_ADD 0xFF0F  // Interrupt Request Register address
//#endif



#endif