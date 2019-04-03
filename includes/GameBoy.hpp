#ifndef GAMEBOY_H
#define GAMEBOY_H

#include <string>
#include "utility.hpp"
#include "cpu.hpp"
#include "memory.hpp"
#include "interrupts.hpp"
#include "instruction.hpp"
#include "rom.hpp"
#include "timer.hpp"
#include <vector>
#include <chrono>
#include <ctime>
#include <ncurses.h>

//#include "display.hpp"
//#include "gpu.hpp"

//namespace GBemulator{
    class GameBoy{
        private:
            Memory memory;
            Cpu cpu;
            //InterruptHandler interruptHandler;
            Rom rom;
            WINDOW* window; // gameboy screen
            Timer timer;
            std::vector<BYTE> testRom;
            unsigned long clockCycles;

                    
            std::chrono::time_point<std::chrono::system_clock> hostOldTime;
            //std::chrono::time_point<std::chrono::system_clock> targetOldTime;
            unsigned long targetOldTime;    
            //Gpu gpu;
            //Display display;
        public:
            GameBoy();
            GameBoy(std::string);
            bool checkCartridge(void);
            bool loadGame(void);
            void playGame(void);
            void sync(void);
            void userInput(void);
            void init(void);
            void printRomInfo(void);
            void printNintendoGraphic(void);
            void printByte(WORD);

            ~GameBoy();
        };

  //  }


#endif

