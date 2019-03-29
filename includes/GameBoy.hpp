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
//#include "display.hpp"
//#include "gpu.hpp"

//namespace GBemulator{
    class GameBoy{
        private:
            
            Cpu cpu;
            Memory memory;
            InterruptHnadler interruptHnadler;
            Rom rom;
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
            bool CheckCartridge(void);
            bool LoadGame(void);
            void PlayGame(void);
            void sync(void);

            void PrintRomInfo(void);
            void PrintNintendoGraphic(void);
            void PrintByte(WORD);

            ~GameBoy();
        };

  //  }


#endif

