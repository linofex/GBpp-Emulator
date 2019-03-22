#include "../includes/GameBoy.hpp"

GBemulator::GameBoy::GameBoy(){}
GBemulator::GameBoy::GameBoy(std::string RomFileName){
    //std::cout << "QUI";
     cpu = Cpu();
    // std::cout << "QUI";
     memory = Memory();
    // std::cout << "QUI";
     interruptHnadler = InterruptHnadler();
    // std::cout << "QUI";
     rom = Rom(RomFileName);
    
}

void GBemulator::GameBoy::PrintRomInfo(){
        rom.PrintRomName();
        rom.PrintRamSize();
        rom.PrintRomSize();
        rom.PrintCartridgeType();
        rom.PrintColorType();
        rom.PrintDestCode();
        rom.PrintLicenseCodeOld();
        rom.PrintLicenseCodeNew();
        rom.PrintNintendoGraphic();
        rom.PrintBeginPoint();
}


GBemulator::GameBoy::~GameBoy(){}