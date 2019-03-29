//#pragma once

#ifndef TIMER_H
#define TIMER_H



// //locations for the timers
// #define DIVIDER 0xFF04
// #define TIMA 0xFF05
// #define TMA 0xFF06
// #define TMC 0xFF07

class Memory;
    unsigned long timerCounter;
    unsigned long dividerCounter;

class Timer{
    Memory* memory;
public:
    Timer(Memory*);
    void updateTimers(unsigned long);
    bool isTimerOn(void);
    void setTimer(void);
    void stepDivider(unsigned long);
    void stepTimer(unsigned long);
};
#endif

