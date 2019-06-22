ifeq ($(OS),Windows_NT)
    CFLAGS = -g -std=c++11 -O2 -I .\SDL2\include -L .\SDL2\lib -lSDL2 -lSDL2main
	LDFLAGS = -std=c++11 -lSDL2  -lSDL2main
	CLEAN = del
	INCLUDES = .\includes
	SOURCES = .\sources

	SRCS = ${SOURCES}\main.cpp ${SOURCES}\memory.cpp ${SOURCES}\cpu.cpp \
       ${SOURCES}\lcd.cpp ${SOURCES}\interrupts.cpp ${SOURCES}\GameBoy.cpp \
       ${SOURCES}\dma.cpp ${SOURCES}\instruction.cpp ${SOURCES}\ppu.cpp \
	   ${SOURCES}\rom.cpp ${SOURCES}\timer.cpp

else 
	CFLAGS = -g -std=c++11 -O2 -lSDL2 
	LDFLAGS = -std=c++11 -lSDL2
	CLEAN = rm -f
	INCLUDES = ./includes
	SOURCES = ./sources

	SRCS = ${SOURCES}/main.cpp ${SOURCES}/memory.cpp ${SOURCES}/cpu.cpp \
       ${SOURCES}/lcd.cpp ${SOURCES}/interrupts.cpp ${SOURCES}/GameBoy.cpp \
       ${SOURCES}/dma.cpp ${SOURCES}/instruction.cpp ${SOURCES}/ppu.cpp \
	   ${SOURCES}/rom.cpp ${SOURCES}/timer.cpp
endif

CC = g++ # compilatore
LD = g++ # linker

OBJS = main.o memory.o cpu.o lcd.o \
       interrupts.o GameBoy.o \
       dma.o instruction.o ppu.o \
	   rom.o timer.o

#linking
gameboy: $(OBJS)
#	@echo "linking.."
	${LD} $+ -o $@  ${LDFLAGS} 


# Compilazione
%.o:${SOURCES}/%.cpp
#	@echo "compiling.."
	${CC} -c $< ${CFLAGS}


#depend:
	

clean:
	${CLEAN} $(OBJS) gameboy*


# DO NOT DELETE

main.o: .//includes//GameBoy.hpp .//includes//utility.hpp
main.o: .//includes//cpu.hpp .//includes//memory.hpp
main.o: .//includes//instruction.hpp .//includes//interrupts.hpp
main.o: .//includes//rom.hpp 
main.o: .//includes//lcd.hpp
main.o: .//includes//ppu.hpp .//includes//utility.hpp
memory.o: .//includes//memory.hpp .//includes//utility.hpp
memory.o: .//includes//dma.hpp .//includes//timer.hpp
cpu.o: .//includes//cpu.hpp .//includes//utility.hpp
cpu.o: .//includes//memory.hpp .//includes//instruction.hpp
cpu.o: .//includes//cpu.hpp .//includes//interrupts.hpp
lcd.o: .//includes//lcd.hpp .//includes//utility.hpp
lcd.o: .//includes//ppu.hpp
lcd.o: .//includes//memory.hpp .//includes//memory.hpp
lcd.o: .//includes//interrupts.hpp
interrupts.o: .//includes//interrupts.hpp .//includes//utility.hpp
interrupts.o: .//includes//memory.hpp .//includes//cpu.hpp
interrupts.o: .//includes//memory.hpp .//includes//instruction.hpp
interrupts.o: .//includes//cpu.hpp
GameBoy.o: .//includes//GameBoy.hpp .//includes//utility.hpp
GameBoy.o: .//includes//cpu.hpp .//includes//memory.hpp
GameBoy.o: .//includes//instruction.hpp .//includes//interrupts.hpp
GameBoy.o: .//includes//rom.hpp
GameBoy.o: .//includes//lcd.hpp
GameBoy.o: .//includes//timer.hpp
GameBoy.o: .//includes//ppu.hpp 
dma.o: .//includes//dma.hpp .//includes//utility.hpp
dma.o: .//includes//memory.hpp .//includes//utility.hpp
instruction.o: .//includes//instruction.hpp .//includes//cpu.hpp
instruction.o: .//includes//utility.hpp .//includes//memory.hpp
instruction.o: .//includes//instruction.hpp
ppu.o: .//includes//ppu.hpp .//includes//memory.hpp
ppu.o: .//includes//utility.hpp 
timer.o: .//includes//timer.hpp .//includes//utility.hpp
timer.o: .//includes//memory.hpp .//includes//utility.hpp
timer.o: .//includes//interrupts.hpp
