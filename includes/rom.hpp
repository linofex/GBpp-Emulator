#ifndef ROM_H
#define ROM_H

#include"utility.hpp"
#include <fstream>
#include <string.h>
#include <vector>
#include <iostream>
#include <iterator>

//namespace GBemulator {

    class Rom{
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
            std::vector<BYTE> game;               // 
        public:
            Rom();
            ~Rom();
            Rom (const std::string t_RomFileName);
            void PrintRomName() const;
            std::vector<BYTE> GetNintendoLogo()const;
            std::vector<BYTE> GetRomName()const;
            std::vector<BYTE> GetRom()const{ return game; };
            void PrintNintendoGraphic()const;
            // void PrintBeginPoint() const;
            // void PrintRomSize()const;
            // void PrintRamSize()const;
            // void PrintCartridgeType() const;
            // void PrintColorType() const;
            // void PrintDestCode() const;
            // void PrintLicenseCodeOld() const;
            //void PrintLicenseCodeNew()const;
            //inline std::vector<BYTE> GetBeginPort() const;

           

    };
// }
#endif