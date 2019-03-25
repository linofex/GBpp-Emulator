#ifndef GAMEBOY_H
#define GAMEBOY_H

#include <string>
#include "utility.hpp"
#include "cpu.hpp"
#include "memory.hpp"
#include "interrupts.hpp"
#include "instruction.hpp"
#include "rom.hpp"
#include <vector>
//#include "display.hpp"
//#include "gpu.hpp"

//namespace GBemulator{
    class GameBoy{
        private:
            
            Cpu cpu;
            Memory memory;
            InterruptHnadler interruptHnadler;
            Rom rom;
            std::vector<BYTE> testRom;
            //Gpu gpu;
            //Display display;
        public:
            GameBoy();
            GameBoy(std::string t_RomFileName);
            bool CheckCartridge();
            bool LoadGame();
            void PlayGame();
            void PrintRomInfo();
            void PrintNintendoGraphic();
            void PrintByte(WORD t_add);
            ~GameBoy();
        };

  //  }


#endif

