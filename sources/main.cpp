#include "../includes/rom.hpp"
#include "../includes/memory.hpp"

using namespace GBemulator;
int main(){
    Rom rr = Rom("../roms/zelda.gb");
    rr.PrintRomName();
}