#include "../includes/dma.hpp"
#include "../includes/utility.hpp"
#include "../includes/memory.hpp"

void startDMATransfer(Memory* t_memory){
    WORD startIndex = t_memory->readByte(DMA);
    startIndex <<= 8; // *100h
    for(BYTE i = 0; i < 0xA0; ++i){
        t_memory->writeByte(0xFE00 + i , t_memory->readByte(startIndex + i));
    }
}
