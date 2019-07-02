#include "../includes/rom.hpp"

#include<iostream>
#include<iomanip>
#include <string> 
#include <algorithm> 
#include <sstream> 
#include <iterator> 


Rom::Rom(){}
Rom::~Rom(){
}

Rom::Rom(const std::string t_RomFileName){                
    RomFileName = t_RomFileName;
}


bool Rom::loadRom(){
    std::ifstream ROMFile(RomFileName.c_str(), std::ifstream::ate | std::ifstream::binary);
    int size;
    int curPos;
    if (ROMFile.is_open()){
        size = ROMFile.tellg();
        game.resize(size);
        ROMFile.seekg (0x00, ROMFile.beg); // Set the pointer at 0x000
        ROMFile.read((char*)game.data(), game.size());  // Read 4 bytes of Beginport
        return true;
    }
    else{
        std::cerr << "[ERROR] Unable to open file";
        return false;
    }
}

BYTE Rom::getRomByte(BYTE t_currentRomBank, WORD t_addr){
    return game.at(t_currentRomBank*0x4000 + t_addr);
}

void Rom::printRomName() const {
    std::vector<BYTE>::const_iterator it = game.begin() + 0x0134;
    for (; it <= game.begin() + 0x0142; ++it){std::cout << *it;}
    std::cout << std::endl;
}

void Rom::printNintendoGraphic() const {
    std::cout << "Nintendo Graphic: ";
    std::vector<BYTE>::const_iterator it = game.begin() + 0x0104;
    for (; it <= game.begin()+0x0133; ++it){std::cout << std::hex << (unsigned int)*it << " ";}
    std::cout << std::endl;

}

std::vector<BYTE> Rom::getNintendoLogo()const{
    std::vector<BYTE>::const_iterator begin = game.begin() + 0x0104;
    std::vector<BYTE>::const_iterator end = game.begin() + 0x0134;
    return std::vector<BYTE>(begin, end);
}

std::string Rom::getRomName()const{
    std::vector<BYTE>::const_iterator begin = game.begin() + 0x0134;
    std::vector<BYTE>::const_iterator end = game.begin() + 0x0143;
    std::vector<BYTE> v = std::vector<BYTE>(begin, end);
    std::ostringstream vts; 
  
    if (!v.empty()) 
    { 
        std::copy(v.begin(), v.end(), std::ostream_iterator<BYTE>(vts)); 
    }
    return vts.str();
}