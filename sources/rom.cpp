#include "../includes/rom.hpp"

Rom::Rom(){}
Rom::Rom (const std::string t_RomFileName){                
    std::ifstream ROMFile(t_RomFileName.c_str(), std::ifstream::ate | std::ifstream::binary);
    int size;
    int curPos;
    // BeginPoint.resize(4);
    // NintendoLogo.resize(48);
    // RomName.resize(15, 0x00);
    
    if (ROMFile.is_open()){
        size = ROMFile.tellg();
        game.resize(size);
        ROMFile.seekg (0x00, ROMFile.beg); // Set the pointer at 0x100
        ROMFile.read((char*)game.data(), game.size());  // Read 4 bytes of Beginport
    }
        else std::cout << "Unable to open file";
}


void Rom::PrintRomName() const{
    std::cout << "ROM name: ";
    std::vector<BYTE>::const_iterator it = game.begin() + 0x0134;
    for (; it <= game.begin() + 0x0142; ++it){std::cout << *it;}
    std::cout << std::endl;
}

void Rom::PrintNintendoGraphic() const {
    std::cout << "Nintendo Graphic: ";
    std::vector<BYTE>::const_iterator it = game.begin() + 0x0104;
    for (; it <= game.begin()+0x0133; ++it){std::cout << std::hex << (unsigned int)*it << " ";}
    std::cout << std::endl;

}

std::vector<BYTE> Rom::GetNintendoLogo()const{
    std::vector<BYTE>::const_iterator begin = game.begin() + 0x0104;
    std::vector<BYTE>::const_iterator end = game.begin() + 0x0133;
    return std::vector<BYTE>(begin, end);
}

std::vector<BYTE> Rom::GetRomName()const{
    std::vector<BYTE>::const_iterator begin = game.begin() + 0x0134;
    std::vector<BYTE>::const_iterator end = game.begin() + 0x0142;
    return std::vector<BYTE>(begin, end);
}



// void Rom::PrintBeginPoint() const{
//     std::cout << "BeginPoint instruction: ";
//     std::vector<BYTE>::const_iterator it = game.begin()+100;
//     for (; it <= game.begin()+104; ++it){std::cout <<  std::hex << (unsigned int)*it;}
//     std::cout << std::endl;
// }
// void Rom::PrintRomSize() const {std::cout <<"Rom size: "<< (int)ROMSize << std::endl;}
// void Rom::PrintRamSize() const {std::cout <<"Ram size: "<< (int)RAMSize << std::endl;}
// void Rom::PrintLicenseCodeNew() const {std::cout <<"License Code New: "<< std::hex << LicenseCodeHigh <<std::hex << LicenseCodeLow<< std::endl;}

// void Rom::PrintCartridgeType() const {std::cout <<"Cartridge type: "<< (int)CartridgeType << std::endl;}
// void Rom::PrintColorType() const {std::cout << "Color type: "<<(int)ColorFlag<< std::endl;}
// void Rom::PrintDestCode() const {std::cout << "Destination Code: "<<(int)DestCode<< std::endl;}
// void Rom::PrintLicenseCodeOld() const {std::cout << "License Code Old: "<<(int)LicenseCode<< std::endl;}
