#ifndef GAMEBOY_H
#define GAMEBOY_H


#include "utility.hpp"
#include "cpu.hpp"
#include "memory.hpp"
#include "interrupts.hpp"
#include "instruction.hpp"
#include "rom.hpp"
#include "lcd.hpp"
#include "timer.hpp"
#include "ppu.hpp"

#include <vector>
#include <chrono>
#include <ctime>
#include <string>
#include <SDL2/SDL.h>
//#include <ncurses.h>


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
            SDL_Texture* texture;
            Timer timer; //gameboy timer
            std::vector<Uint32> times;
            std::vector<BYTE> testRom;
            const Uint8* keyState;
            
            //unsigned long clockCycles;
            SDL_Event event;
            
            //std::chrono::time_point<std::chrono::system_clock> targetOldTime;
            Uint64 targetOldTime;   
            Uint32 displayTime; 
            Uint64 hostOldTime;
            Uint32 lcdLastTime;
            Uint32 onesecond;
            double accumulator; 
            
            //Uint64 hostNewTime;
            Uint64 hostFrequency;

            //Gpu gpu;
            //Display display;
            void pressedKey(BYTE);
            void releasedKey(BYTE);
        public:
            long long int o;
            GameBoy();
            GameBoy(std::string);
            bool checkCartridge(void);
            bool loadGame(void);
            void boot(void);
            void playGame(void);
            void sync(void);
            void refreshLcdScreen(void);
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

