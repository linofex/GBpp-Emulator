#include "../includes/GameBoy.hpp"
#include <vector>
// /GameBoy::GameBoy(){}
GameBoy::GameBoy(std::string t_RomFileName):cpu(), memory(), interruptHnadler(), rom(t_RomFileName), timer(&memory){ 
    testRom = std::vector<BYTE> {0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 0x03, 0x73,
                        		 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D, 0x00, 0x08, 0x11, 0x1F, 
                        		 0x88, 0x89, 0x00, 0x0E, 0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 
                       			 0xD9, 0x99, 0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC, 
                       			 0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E
    							};
    clockCycles = 0;
    targetOldTime = TARGETPERIOD * clockCycles; //0
    hostOldTime = std::chrono::system_clock::now();
}

bool GameBoy::LoadGame(){
	if(CheckCartridge()){
		std::vector<BYTE> game(rom.GetRom());
		WORD address = 0x0000;
		std::vector<BYTE>::iterator it = game.begin();
		for(; it != game.end() ; ++it){
			if(address <= 0x8000){
				memory.writeByte(address++, *it);
			}
			else{
				std::cout<< "Not enough memory";
				return false;
			}
		}
		return true;
	}  
	return false;
}

void GameBoy::PlayGame(){
	//clockCycles += cpu.step();
        
}

void GameBoy::PrintByte(WORD t_add){
    std::cout << memory.readByte(t_add); 
}
void GameBoy::PrintNintendoGraphic(){
	rom.PrintNintendoGraphic();
	std::cout<< "Nintendo Graphic: ";
	std::vector<BYTE>::const_iterator it = testRom.begin();
    for (; it != testRom.end(); ++it){std::cout << std::hex << (unsigned int)*it << " ";}
    std::cout << std::endl;
        
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

void GameBoy::sync(){
	std::chrono::time_point<std::chrono::system_clock>hostNewTime = std::chrono::system_clock::now();
    std::chrono::duration<double> hostElapsedTimeC = hostNewTime - hostOldTime;
    unsigned int hostElapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(hostElapsedTimeC).count();
    std::cout<<"The host elapsed time is: "<<'\t'<<hostElapsedTime<<std::endl;

    unsigned int targetNewTime = TARGETPERIOD * clockCycles;
    unsigned int targetElapsedTime = targetNewTime - targetOldTime;
    std::cout<<"The target elapsed time is: "<<'\t'<<targetElapsedTime<<std::endl;
    

    if((targetElapsedTime - hostElapsedTime) > (2/10^3))     //2 ms
        std::cout<<"The diff is: "<<'\t'<<targetElapsedTime - hostElapsedTime<<std::endl;
        //Sleep(diff);

    hostOldTime = hostNewTime;
    targetOldTime = targetNewTime;
}

GameBoy::~GameBoy(){
    std::cout << "GAMEBOY distruttore\n";
}