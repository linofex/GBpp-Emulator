#include "../includes/GameBoy.hpp"
#include <vector>
GameBoy::GameBoy(){}
GameBoy::GameBoy(std::string t_RomFileName):cpu(), memory(), interruptHnadler(), rom(t_RomFileName){
//         std::cout<<"j";
//     //std::cout << "QUI";
//      rom = new Rom(t_RomFileName);
//      memory = Memory();
//      std::cout << "QUI";
//      cpu = Cpu(&memory);
//      std::cout << "QUI";
//      std::cout << "QUI";
//      interruptHnadler = InterruptHnadler();
//      std::cout << "QUI";
     
     std::vector<BYTE> v {0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 0x03, 0x73,
                0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D, 0x00, 0x08, 0x11, 0x1F, 
                0x88, 0x89, 0x00, 0x0E, 0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 
                0xD9, 0x99, 0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xE5, 0xCC, 
                0xDD, 0xDD, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E
     };
     testRom = v;
}

void GameBoy::LoadGame(){
        if(CheckCartridge()){
                // std::vector<BYTE> Game = rom.GetRom();
                // BYTE address = 0x0000;
                // std::vector<BYTE>::iterator it = Game.begin();
                // for(; it != Game.end() ; ++it){
                //         if(address <= 0x8000){
                //                 memory.writeByte(address++, *it);
                //         }
                //         else{
                //                 std::cout<< "Not enough memory";
                //         }
                // }
        }
}
void GameBoy::PrintRomInfo(){
        rom.PrintRomName();
        // rom.PrintRamSize();
        // rom.PrintRomSize();
        // rom.PrintCartridgeType();
        // rom.PrintColorType();
        // rom.PrintDestCode();
        // rom.PrintLicenseCodeOld();
        // rom.PrintLicenseCodeNew();
         rom.PrintNintendoGraphic();
        //rom.PrintBeginPoint();
}
bool GameBoy::CheckCartridge(){
        return rom.GetNintendoLogo() == testRom;
}

GameBoy::~GameBoy(){}