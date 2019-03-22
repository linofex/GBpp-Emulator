#include "../includes/rom.hpp"
#include "../includes/memory.hpp"

using namespace GBemulator;
int main(int argc, char** argv){
    if (argc == 2){
        std::string romName = "../roms/" + std::string(argv[1]);
        Rom rr = Rom(romName);
        rr.PrintRomName();
        rr.PrintRamSize();
        rr.PrintRomSize();
        rr.PrintCartridgeType();
        rr.PrintColorType();
        rr.PrintDestCode();
        rr.PrintLicenseCodeOld();
        rr.PrintLicenseCodeNew();
        rr.PrintNintendoGraphic();
        rr.PrintBeginPoint();
    }
} 