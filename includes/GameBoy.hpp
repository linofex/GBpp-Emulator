#ifndef GAMEBOY_H
#define GAMEBOY_H

/*
  CPU          - 8-bit (Similar to the Z80 processor)
  Clock Speed  - 4.194304MHz (4.295454MHz for SGB, max. 8.4MHz for CGB)
  Work RAM     - 8K Byte (32K Byte for CGB)
  Video RAM    - 8K Byte (16K Byte for CGB)
  Screen Size  - 2.6"
  Resolution   - 160x144 (20x18 tiles)
  Max sprites  - Max 40 per screen, 10 per line
  Sprite sizes - 8x8 or 8x16
  Palettes     - 1x4 BG, 2x3 OBJ (for CGB: 8x4 BG, 8x3 OBJ)
  Colors       - 4 grayshades (32768 colors for CGB)
  Horiz Sync   - 9198 KHz (9420 KHz for SGB)
  Vert Sync    - 59.73 Hz (61.17 Hz for SGB)
  Sound        - 4 channels with stereo sound
  Power        - DC6V 0.7W (DC3V 0.7W for GB Pocket, DC3V 0.6W for CGB)
*/


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
#include <ctime>
#include <string>
#include <SDL2/SDL.h>



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

