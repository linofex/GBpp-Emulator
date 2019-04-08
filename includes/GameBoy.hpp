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
//#include <ncurses.h>
#include <SDL2/SDL.h>

//#include "display.hpp"
//#include "gpu.hpp"

//namespace GBemulator{
    class GameBoy{
        private:
            Memory memory;
            Cpu cpu;
            //InterruptHandler interruptHandler;
            Rom rom;
            SDL_Window* window; // gameboy screen
            Timer timer; //gameboy timer
            std::vector<Uint32> times;
            std::vector<BYTE> testRom;
            
            unsigned long clockCycles;
            SDL_Event event;
            
            Uint32 hostOldTime;
            //std::chrono::time_point<std::chrono::system_clock> targetOldTime;
            Uint32 targetOldTime;    
            //Gpu gpu;
            //Display display;
            void pressedKey(int);
            void releasedKey(int);
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

