#ifndef GAMEBOY_H
#define GAMEBOY_H

#include <string>
#include "utility.hpp"
#include "cpu.hpp"
#include "memory.hpp"
#include "interrupts.hpp"
#include "instruction.hpp"
#include "rom.hpp"
#include "lcd.hpp"

#include "timer.hpp"
#include <vector>
#include <chrono>
#include <ctime>
//#include <ncurses.h>
#include <SDL2/SDL.h>
#include "ppu.hpp"

//namespace GBemulator{
    class GameBoy{
        private:
            Memory memory;
            Cpu cpu;
            Ppu ppu;
            Lcd lcd;
            //InterruptHandler interruptHandler;
            Rom rom;
            SDL_Window* window; // gameboy screen
            SDL_Renderer* renderer; // gameboy renderer
            Timer timer; //gameboy timer
            std::vector<Uint32> times;
            std::vector<BYTE> testRom;
            
            unsigned long clockCycles;
            SDL_Event event;
            
            Uint32 hostOldTime;
            //std::chrono::time_point<std::chrono::system_clock> targetOldTime;
            Uint32 targetOldTime;   
            Uint32 displayTime; 
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
            void initSDL(void);
            void printRomInfo(void);
            void printNintendoGraphic(void);
            void printByte(WORD);
            ~GameBoy();
        };

  //  }


#endif

