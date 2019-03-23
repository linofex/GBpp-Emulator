//#include "../includes/rom.hpp"
//#include "../includes/memory.hpp"
#include "../includes/GameBoy.hpp"
//#include "../includes/cpu.hpp"

//using namespace GBemulator;
int main(int argc, char** argv){
    if (argc == 2){
        std::string romName = "../roms/" + std::string(argv[1]);
        GameBoy gameboy = GameBoy(romName);
        
       gameboy.PrintRomInfo();
    }
    
            

} 