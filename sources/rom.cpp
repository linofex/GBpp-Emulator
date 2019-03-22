#include "../includes/rom.hpp"

GBemulator::Rom::Rom (const std::string t_RomFileName){                
    std::ifstream ROMFile(t_RomFileName.c_str(), std::ifstream::ate | std::ifstream::binary);
    int size;
    int curPos;
    BeginPoint.resize(4);
    NintendoLogo.resize(48);
    RomName.resize(15, 0x00);
    
    if (ROMFile.is_open()){
        size = ROMFile.tellg();
        ROMFile.seekg (0x100, ROMFile.beg); // Set the pointer at 0x100
        ROMFile.read((char*)BeginPoint.data(), BeginPoint.size());  // Read 4 bytes of Beginport
        ROMFile.read((char*)NintendoLogo.data(), NintendoLogo.size());  // Read 48 bytes of NintendoLogo
        ROMFile.read((char*)RomName.data(), RomName.size());  // Read 16 bytes of RomName
        ROMFile.read((char*)&ColorFlag, 1);  
        ROMFile.read((char*)&LicenseCodeHigh, 1);  
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
        Game.resize(size - (curPos + 2)); // Allocate the space needed for the game
                                        // +2 since the checksum is not needed
        ROMFile.read((char*)Game.data(), size - curPos);  
    }
        else std::cout << "Unable to open file";
}
void GBemulator::Rom::PrintBeginPoint() const{
    std::cout << "BeginPoint instruction: ";
    std::vector<BYTE>::const_iterator it = BeginPoint.begin();
    for (; it != BeginPoint.end(); ++it){std::cout << (unsigned int)*it;}
    std::cout << std::endl;
}

void GBemulator::Rom::PrintRomName() const{
    std::cout << "ROM name: ";
    std::vector<BYTE>::const_iterator it = RomName.begin();
    for (; it != RomName.end(); ++it){std::cout << *it;}
    std::cout << std::endl;
}

void GBemulator::Rom::PrintNintendoGraphic() const {
    std::cout << "Nintendo Graphic: ";
    std::vector<BYTE>::const_iterator it = NintendoLogo.begin();
    for (; it != NintendoLogo.end(); ++it){std::cout << std::hex << (unsigned int)*it << " ";}
    std::cout << std::endl;

}
void GBemulator::Rom::PrintRomSize() const {std::cout <<"Rom size: "<< (int)ROMSize << std::endl;}
void GBemulator::Rom::PrintRamSize() const {std::cout <<"Ram size: "<< (int)RAMSize << std::endl;}
void GBemulator::Rom::PrintLicenseCodeNew() const {std::cout <<"License Code New: "<< std::hex << LicenseCodeHigh <<std::hex << LicenseCodeLow<< std::endl;}

void GBemulator::Rom::PrintCartridgeType() const {std::cout <<"Cartridge type: "<< (int)CartridgeType << std::endl;}
void GBemulator::Rom::PrintColorType() const {std::cout << "Color type: "<<(int)ColorFlag<< std::endl;}
void GBemulator::Rom::PrintDestCode() const {std::cout << "Destination Code: "<<(int)DestCode<< std::endl;}
void GBemulator::Rom::PrintLicenseCodeOld() const {std::cout << "License Code Old: "<<(int)LicenseCode<< std::endl;}
