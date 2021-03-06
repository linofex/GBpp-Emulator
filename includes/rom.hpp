#ifndef ROM_H
#define ROM_H

#include"utility.hpp"
#include <fstream>
#include <string.h>
#include <vector>
#include <iostream>

class Rom {
    private:

        // std::vector<BYTE> BeginPoint;     // 0100-0103 This is the begin code execution point in a cart                     
        // std::vector<BYTE> NintendoLogo;  // 0104-0133 Scrolling Nintendo graphic
        // std::vector<BYTE> RomName;       // 0134-0142 Title of the game in UPPER CASE ASCII.
        // BYTE ColorFlag;         // 0143 Color GB
        // BYTE LicenseCodeHigh;   // 0144 High nibble License Code ASCII
        // BYTE LicenseCodeLow;    // 0145 Low nibble License Code ASCII
        // BYTE GBIndicator;       // 0146 0x00 = GB
        // BYTE CartridgeType;      // 0147 Cartridge Type
        // BYTE ROMSize;           // 0148 ROM Size
        // BYTE RAMSize;           // 0149 RAM Size
        // BYTE DestCode;          // 014A Destination Code
        // BYTE LicenseCode;       // 014B License Code (old)
        // BYTE MaskROM;           // 014C Mask ROM Version Number
        // BYTE CompCheck;         // 014D Complement check
        //                         // 014E-014F Checksum not needed for GB
        std::vector<BYTE> game;
        std::string RomFileName;
    public:
        Rom();
        ~Rom();
        Rom (const std::string t_RomFileName);
        void printRomName() const;
        bool loadRom(void);
        std::vector<BYTE> getNintendoLogo()const;
        std::string getRomName()const;
        const std::vector<BYTE>* getRom()const{ return &game; };
        inline BYTE getRomBank() const {return game.at(0x147);}
        BYTE getRomByte(BYTE, WORD);

        void printNintendoGraphic()const;

};

#endif