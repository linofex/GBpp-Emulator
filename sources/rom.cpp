#include "../includes/rom.hpp"

GBemulator::Rom::Rom (const char* t_RomFileName){                
    std::ifstream ROMFile(t_RomFileName, std::ifstream::ate | std::ifstream::binary);
    int size;
    int curPos;
    BeginPoint.resize(4);
    NintendoLogo.resize(48);
    RomName.resize(16, 0x00);
    
    if (ROMFile.is_open()){
        size = ROMFile.tellg();
        ROMFile.seekg (0x100, ROMFile.beg); // Set the pointer at 0x100
        ROMFile.read((char*)BeginPoint.data(), BeginPoint.size());  // Read 4 bytes of Beginport
        ROMFile.read((char*)NintendoLogo.data(), NintendoLogo.size());  // Read 48 bytes of NintendoLogo
        ROMFile.read((char*)RomName.data(), RomName.size());  // Read 16 bytes of RomName
        ROMFile.read((char*)&ColorFlag, 1);  
        ROMFile.read((char*)&LicenseCode, 1);  
        ROMFile.read((char*)&LicenseCodeLow, 1);  
        ROMFile.read((char*)&GBIndicator, 1);  
        ROMFile.read((char*)&CartridgeType, 1);  
        ROMFile.read((char*)&ROMSize, 1);                      
        ROMFile.read((char*)&RAMSize, 1);                      
        ROMFile.read((char*)&DestCode, 1);                      
        ROMFile.read((char*)&LicenseCode, 1);  
        ROMFile.read((char*)&MaskROM, 1);  
        ROMFile.read((char*)&CompCheck, 1);  
        curPos = ROMFile.tellg(); // Get current position
        Game.resize(size - curPos); // Allocate the space nedded for the game
        ROMFile.read((char*)Game.data(), size - curPos);  
    }
        else std::cout << "Unable to open file";
}

void GBemulator::Rom::PrintRomName() const{
    std::vector<BYTE>::const_iterator it = RomName.begin();
    for (; it != RomName.end(); ++it){std::cout << *it;}
}