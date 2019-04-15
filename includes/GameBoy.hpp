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
            
            //unsigned long clockCycles;
            SDL_Event event;
            
            //std::chrono::time_point<std::chrono::system_clock> targetOldTime;
            Uint64 targetOldTime;   
            Uint32 displayTime; 
            Uint64 hostOldTime;
            //Uint64 hostNewTime;
            Uint64 hostFrequency;

            //Gpu gpu;
            //Display display;
            void pressedKey(int);
            void releasedKey(int);
        public:
            long long int o;
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
            void turnOff(void);
            ~GameBoy();
        };

  //  }


#endif

