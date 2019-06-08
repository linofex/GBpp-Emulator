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
            Rom rom;
            Timer timer; //gameboy timer

            //SDL setup
            SDL_Window* window; // gameboy screen
            SDL_Renderer* renderer; // gameboy renderer
            SDL_Texture* texture; // gameboy texture
            SDL_Event event;
           
            std::vector<BYTE> testRom;
            const Uint8* keyState;
 
            float hostOldTime;
            float accumulator; 
            
            //Uint64 hostNewTime;
            Uint64 hostFrequency;

            //Gpu gpu;
            //Display display;
            void pressedKey(BYTE);
            void releasedKey(BYTE);
        public:
            GameBoy();
            GameBoy(std::string);
            bool checkCartridge(void);
            bool loadGame(void);
            void boot(void);
            void playGame(void);
            void sync(void);
            void userInput(void);
            void initSDL(void);

            void turnOff(void);
            ~GameBoy();
        };

  //  }


#endif

