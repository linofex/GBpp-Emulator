CC = g++ # compilatore
LD = g++ # linker
CFLAGS = -g -std=c++11 -O2 -lSDL2 
LDFLAGS = -std=c++11 -O2 -lSDL2 
INCLUDES = ./includes
SOURCES = ./sources

SRCS = ${SOURCES}/main.cpp ${SOURCES}/memory.cpp ${SOURCES}/cpu.cpp \
       ${SOURCES}/lcd.cpp ${SOURCES}/interrupts.cpp ${SOURCES}/GameBoy.cpp \
       ${SOURCES}/dma.cpp ${SOURCES}/instruction.cpp ${SOURCES}/ppu.cpp \
	   ${SOURCES}/rom.cpp ${SOURCES}/timer.cpp

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


depend:
	@makedepend -- $(CFLAGS) -- $(SRCS)

clean:
	rm -f GameBoy $(OBJS)


# DO NOT DELETE

main.o: ./includes/GameBoy.hpp ./includes/utility.hpp
main.o: ./includes/cpu.hpp ./includes/memory.hpp
main.o: ./includes/instruction.hpp ./includes/interrupts.hpp
main.o: ./includes/rom.hpp /usr/include/string.h
main.o: /usr/include/features.h /usr/include/stdc-predef.h
main.o: /usr/include/xlocale.h ./includes/lcd.hpp
main.o: /usr/include/SDL2/SDL.h /usr/include/SDL2/SDL_main.h
main.o: /usr/include/SDL2/SDL_stdinc.h
main.o: /usr/include/SDL2/SDL_config.h
main.o: /usr/include/SDL2/SDL_platform.h
main.o: /usr/include/SDL2/begin_code.h
main.o: /usr/include/SDL2/close_code.h /usr/include/stdio.h
main.o: /usr/include/libio.h /usr/include/_G_config.h
main.o: /usr/include/wchar.h /usr/include/stdlib.h
main.o: /usr/include/alloca.h /usr/include/strings.h
main.o: /usr/include/inttypes.h /usr/include/stdint.h
main.o: /usr/include/ctype.h /usr/include/endian.h
main.o: /usr/include/math.h /usr/include/iconv.h
main.o: /usr/include/SDL2/SDL_assert.h
main.o: /usr/include/SDL2/SDL_atomic.h
main.o: /usr/include/SDL2/SDL_audio.h /usr/include/SDL2/SDL_error.h
main.o: /usr/include/SDL2/SDL_endian.h
main.o: /usr/include/SDL2/SDL_mutex.h
main.o: /usr/include/SDL2/SDL_thread.h
main.o: /usr/include/SDL2/SDL_rwops.h
main.o: /usr/include/SDL2/SDL_clipboard.h
main.o: /usr/include/SDL2/SDL_cpuinfo.h
main.o: /usr/include/SDL2/SDL_events.h
main.o: /usr/include/SDL2/SDL_video.h
main.o: /usr/include/SDL2/SDL_pixels.h /usr/include/SDL2/SDL_rect.h
main.o: /usr/include/SDL2/SDL_surface.h
main.o: /usr/include/SDL2/SDL_blendmode.h
main.o: /usr/include/SDL2/SDL_keyboard.h
main.o: /usr/include/SDL2/SDL_keycode.h
main.o: /usr/include/SDL2/SDL_scancode.h
main.o: /usr/include/SDL2/SDL_mouse.h
main.o: /usr/include/SDL2/SDL_joystick.h
main.o: /usr/include/SDL2/SDL_gamecontroller.h
main.o: /usr/include/SDL2/SDL_quit.h
main.o: /usr/include/SDL2/SDL_gesture.h
main.o: /usr/include/SDL2/SDL_touch.h
main.o: /usr/include/SDL2/SDL_filesystem.h
main.o: /usr/include/SDL2/SDL_haptic.h
main.o: /usr/include/SDL2/SDL_hints.h
main.o: /usr/include/SDL2/SDL_loadso.h /usr/include/SDL2/SDL_log.h
main.o: /usr/include/SDL2/SDL_messagebox.h
main.o: /usr/include/SDL2/SDL_power.h
main.o: /usr/include/SDL2/SDL_render.h
main.o: /usr/include/SDL2/SDL_system.h
main.o: /usr/include/SDL2/SDL_timer.h
main.o: /usr/include/SDL2/SDL_version.h ./includes/timer.hpp
main.o: ./includes/ppu.hpp ./includes/utility.hpp
memory.o: ./includes/memory.hpp ./includes/utility.hpp
memory.o: ./includes/dma.hpp ./includes/timer.hpp
cpu.o: ./includes/cpu.hpp ./includes/utility.hpp
cpu.o: ./includes/memory.hpp ./includes/instruction.hpp
cpu.o: ./includes/cpu.hpp ./includes/interrupts.hpp
cpu.o: /usr/include/unistd.h /usr/include/features.h
cpu.o: /usr/include/stdc-predef.h /usr/include/getopt.h
lcd.o: ./includes/lcd.hpp ./includes/utility.hpp
lcd.o: /usr/include/SDL2/SDL.h /usr/include/SDL2/SDL_main.h
lcd.o: /usr/include/SDL2/SDL_stdinc.h
lcd.o: /usr/include/SDL2/SDL_config.h
lcd.o: /usr/include/SDL2/SDL_platform.h
lcd.o: /usr/include/SDL2/begin_code.h
lcd.o: /usr/include/SDL2/close_code.h /usr/include/stdio.h
lcd.o: /usr/include/features.h /usr/include/stdc-predef.h
lcd.o: /usr/include/libio.h /usr/include/_G_config.h
lcd.o: /usr/include/wchar.h /usr/include/stdlib.h
lcd.o: /usr/include/alloca.h /usr/include/string.h
lcd.o: /usr/include/xlocale.h /usr/include/strings.h
lcd.o: /usr/include/inttypes.h /usr/include/stdint.h
lcd.o: /usr/include/ctype.h /usr/include/endian.h
lcd.o: /usr/include/math.h /usr/include/iconv.h
lcd.o: /usr/include/SDL2/SDL_assert.h
lcd.o: /usr/include/SDL2/SDL_atomic.h /usr/include/SDL2/SDL_audio.h
lcd.o: /usr/include/SDL2/SDL_error.h /usr/include/SDL2/SDL_endian.h
lcd.o: /usr/include/SDL2/SDL_mutex.h /usr/include/SDL2/SDL_thread.h
lcd.o: /usr/include/SDL2/SDL_rwops.h
lcd.o: /usr/include/SDL2/SDL_clipboard.h
lcd.o: /usr/include/SDL2/SDL_cpuinfo.h
lcd.o: /usr/include/SDL2/SDL_events.h /usr/include/SDL2/SDL_video.h
lcd.o: /usr/include/SDL2/SDL_pixels.h /usr/include/SDL2/SDL_rect.h
lcd.o: /usr/include/SDL2/SDL_surface.h
lcd.o: /usr/include/SDL2/SDL_blendmode.h
lcd.o: /usr/include/SDL2/SDL_keyboard.h
lcd.o: /usr/include/SDL2/SDL_keycode.h
lcd.o: /usr/include/SDL2/SDL_scancode.h
lcd.o: /usr/include/SDL2/SDL_mouse.h
lcd.o: /usr/include/SDL2/SDL_joystick.h
lcd.o: /usr/include/SDL2/SDL_gamecontroller.h
lcd.o: /usr/include/SDL2/SDL_quit.h /usr/include/SDL2/SDL_gesture.h
lcd.o: /usr/include/SDL2/SDL_touch.h
lcd.o: /usr/include/SDL2/SDL_filesystem.h
lcd.o: /usr/include/SDL2/SDL_haptic.h /usr/include/SDL2/SDL_hints.h
lcd.o: /usr/include/SDL2/SDL_loadso.h /usr/include/SDL2/SDL_log.h
lcd.o: /usr/include/SDL2/SDL_messagebox.h
lcd.o: /usr/include/SDL2/SDL_power.h /usr/include/SDL2/SDL_render.h
lcd.o: /usr/include/SDL2/SDL_system.h /usr/include/SDL2/SDL_timer.h
lcd.o: /usr/include/SDL2/SDL_version.h ./includes/ppu.hpp
lcd.o: ./includes/memory.hpp ./includes/memory.hpp
lcd.o: ./includes/interrupts.hpp
interrupts.o: ./includes/interrupts.hpp ./includes/utility.hpp
interrupts.o: ./includes/memory.hpp ./includes/cpu.hpp
interrupts.o: ./includes/memory.hpp ./includes/instruction.hpp
interrupts.o: ./includes/cpu.hpp
GameBoy.o: ./includes/GameBoy.hpp ./includes/utility.hpp
GameBoy.o: ./includes/cpu.hpp ./includes/memory.hpp
GameBoy.o: ./includes/instruction.hpp ./includes/interrupts.hpp
GameBoy.o: ./includes/rom.hpp /usr/include/string.h
GameBoy.o: /usr/include/features.h /usr/include/stdc-predef.h
GameBoy.o: /usr/include/xlocale.h ./includes/lcd.hpp
GameBoy.o: /usr/include/SDL2/SDL.h /usr/include/SDL2/SDL_main.h
GameBoy.o: /usr/include/SDL2/SDL_stdinc.h
GameBoy.o: /usr/include/SDL2/SDL_config.h
GameBoy.o: /usr/include/SDL2/SDL_platform.h
GameBoy.o: /usr/include/SDL2/begin_code.h
GameBoy.o: /usr/include/SDL2/close_code.h /usr/include/stdio.h
GameBoy.o: /usr/include/libio.h /usr/include/_G_config.h
GameBoy.o: /usr/include/wchar.h /usr/include/stdlib.h
GameBoy.o: /usr/include/alloca.h /usr/include/strings.h
GameBoy.o: /usr/include/inttypes.h /usr/include/stdint.h
GameBoy.o: /usr/include/ctype.h /usr/include/endian.h
GameBoy.o: /usr/include/math.h /usr/include/iconv.h
GameBoy.o: /usr/include/SDL2/SDL_assert.h
GameBoy.o: /usr/include/SDL2/SDL_atomic.h
GameBoy.o: /usr/include/SDL2/SDL_audio.h
GameBoy.o: /usr/include/SDL2/SDL_error.h
GameBoy.o: /usr/include/SDL2/SDL_endian.h
GameBoy.o: /usr/include/SDL2/SDL_mutex.h
GameBoy.o: /usr/include/SDL2/SDL_thread.h
GameBoy.o: /usr/include/SDL2/SDL_rwops.h
GameBoy.o: /usr/include/SDL2/SDL_clipboard.h
GameBoy.o: /usr/include/SDL2/SDL_cpuinfo.h
GameBoy.o: /usr/include/SDL2/SDL_events.h
GameBoy.o: /usr/include/SDL2/SDL_video.h
GameBoy.o: /usr/include/SDL2/SDL_pixels.h
GameBoy.o: /usr/include/SDL2/SDL_rect.h
GameBoy.o: /usr/include/SDL2/SDL_surface.h
GameBoy.o: /usr/include/SDL2/SDL_blendmode.h
GameBoy.o: /usr/include/SDL2/SDL_keyboard.h
GameBoy.o: /usr/include/SDL2/SDL_keycode.h
GameBoy.o: /usr/include/SDL2/SDL_scancode.h
GameBoy.o: /usr/include/SDL2/SDL_mouse.h
GameBoy.o: /usr/include/SDL2/SDL_joystick.h
GameBoy.o: /usr/include/SDL2/SDL_gamecontroller.h
GameBoy.o: /usr/include/SDL2/SDL_quit.h
GameBoy.o: /usr/include/SDL2/SDL_gesture.h
GameBoy.o: /usr/include/SDL2/SDL_touch.h
GameBoy.o: /usr/include/SDL2/SDL_filesystem.h
GameBoy.o: /usr/include/SDL2/SDL_haptic.h
GameBoy.o: /usr/include/SDL2/SDL_hints.h
GameBoy.o: /usr/include/SDL2/SDL_loadso.h
GameBoy.o: /usr/include/SDL2/SDL_log.h
GameBoy.o: /usr/include/SDL2/SDL_messagebox.h
GameBoy.o: /usr/include/SDL2/SDL_power.h
GameBoy.o: /usr/include/SDL2/SDL_render.h
GameBoy.o: /usr/include/SDL2/SDL_system.h
GameBoy.o: /usr/include/SDL2/SDL_timer.h
GameBoy.o: /usr/include/SDL2/SDL_version.h ./includes/timer.hpp
GameBoy.o: ./includes/ppu.hpp /usr/include/unistd.h
GameBoy.o: /usr/include/getopt.h
dma.o: ./includes/dma.hpp ./includes/utility.hpp
dma.o: ./includes/memory.hpp ./includes/utility.hpp
instruction.o: ./includes/instruction.hpp ./includes/cpu.hpp
instruction.o: ./includes/utility.hpp ./includes/memory.hpp
instruction.o: ./includes/instruction.hpp
ppu.o: ./includes/ppu.hpp ./includes/memory.hpp
ppu.o: ./includes/utility.hpp /usr/include/SDL2/SDL.h
ppu.o: /usr/include/SDL2/SDL_main.h /usr/include/SDL2/SDL_stdinc.h
ppu.o: /usr/include/SDL2/SDL_config.h
ppu.o: /usr/include/SDL2/SDL_platform.h
ppu.o: /usr/include/SDL2/begin_code.h
ppu.o: /usr/include/SDL2/close_code.h /usr/include/stdio.h
ppu.o: /usr/include/features.h /usr/include/stdc-predef.h
ppu.o: /usr/include/libio.h /usr/include/_G_config.h
ppu.o: /usr/include/wchar.h /usr/include/stdlib.h
ppu.o: /usr/include/alloca.h /usr/include/string.h
ppu.o: /usr/include/xlocale.h /usr/include/strings.h
ppu.o: /usr/include/inttypes.h /usr/include/stdint.h
ppu.o: /usr/include/ctype.h /usr/include/endian.h
ppu.o: /usr/include/math.h /usr/include/iconv.h
ppu.o: /usr/include/SDL2/SDL_assert.h
ppu.o: /usr/include/SDL2/SDL_atomic.h /usr/include/SDL2/SDL_audio.h
ppu.o: /usr/include/SDL2/SDL_error.h /usr/include/SDL2/SDL_endian.h
ppu.o: /usr/include/SDL2/SDL_mutex.h /usr/include/SDL2/SDL_thread.h
ppu.o: /usr/include/SDL2/SDL_rwops.h
ppu.o: /usr/include/SDL2/SDL_clipboard.h
ppu.o: /usr/include/SDL2/SDL_cpuinfo.h
ppu.o: /usr/include/SDL2/SDL_events.h /usr/include/SDL2/SDL_video.h
ppu.o: /usr/include/SDL2/SDL_pixels.h /usr/include/SDL2/SDL_rect.h
ppu.o: /usr/include/SDL2/SDL_surface.h
ppu.o: /usr/include/SDL2/SDL_blendmode.h
ppu.o: /usr/include/SDL2/SDL_keyboard.h
ppu.o: /usr/include/SDL2/SDL_keycode.h
ppu.o: /usr/include/SDL2/SDL_scancode.h
ppu.o: /usr/include/SDL2/SDL_mouse.h
ppu.o: /usr/include/SDL2/SDL_joystick.h
ppu.o: /usr/include/SDL2/SDL_gamecontroller.h
ppu.o: /usr/include/SDL2/SDL_quit.h /usr/include/SDL2/SDL_gesture.h
ppu.o: /usr/include/SDL2/SDL_touch.h
ppu.o: /usr/include/SDL2/SDL_filesystem.h
ppu.o: /usr/include/SDL2/SDL_haptic.h /usr/include/SDL2/SDL_hints.h
ppu.o: /usr/include/SDL2/SDL_loadso.h /usr/include/SDL2/SDL_log.h
ppu.o: /usr/include/SDL2/SDL_messagebox.h
ppu.o: /usr/include/SDL2/SDL_power.h /usr/include/SDL2/SDL_render.h
ppu.o: /usr/include/SDL2/SDL_system.h /usr/include/SDL2/SDL_timer.h
ppu.o: /usr/include/SDL2/SDL_version.h
rom.o: ./includes/rom.hpp ./includes/utility.hpp
rom.o: /usr/include/string.h /usr/include/features.h
rom.o: /usr/include/stdc-predef.h /usr/include/xlocale.h
timer.o: ./includes/timer.hpp ./includes/utility.hpp
timer.o: ./includes/memory.hpp ./includes/utility.hpp
timer.o: ./includes/interrupts.hpp
