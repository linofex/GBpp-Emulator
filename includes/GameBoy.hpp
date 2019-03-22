#ifndef GAMEBOY_H
#define GAMEBOY_H
#include <string>
#include "utility.hpp"
#include "cpu.hpp"
#include "memory.hpp"
#include "interrupts.hpp"
#include "rom.hpp"
//#include "display.hpp"
//#include "gpu.hpp"

namespace GBemulator{
    class GameBoy{
        private:
            Cpu cpu;
            Memory memory;
            InterruptHnadler interruptHnadler;
            Rom rom;
            //Gpu gpu;
            //Display display;
        public:
            GameBoy();
            GameBoy(std::string RomFileName);
            void PrintRomInfo();
            ~GameBoy();
        };

    }


#endif

