# GB-Emulator
A GameBoy emulator written in C++. This project was developed for the "Emulation and virtualization" course at University of Pisa.

It works on Linux and Windows platforms. 

## Useful links

- Pandocs specification. Everything You Always Wanted To Know About GAMEBOY - [link](http://bgb.bircd.org/pandocs.htm)

- Very useful video about the gameboy - [link](https://media.ccc.de/v/33c3-8029-the_ultimate_game_boy_talk)
 
- Table for correct instruction opcodes and CPU cycles - [link](http://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html)

- GameBoy manual - [link](https://realboyemulator.files.wordpress.com/2013/01/gbcpuman.pdf)

- Useful developing control flow of the emulator - [link](http://www.codeslinger.co.uk/pages/projects/gameboy.html)

## Useful debugging tools
- Useful tool to evaluate the correctness of the emulator - [link](http://bgb.bircd.org/)
- Test roms for instructions debugging. (Already present in /roms/individual directory) - [link](https://github.com/retrio/gb-test-roms).


## Controls


| Gameboy  | Emulator |
| ------------- | ------------- |
| A  |   a |
| B  | s |
| UP  | up key  |
| DOWN  | down key  |
| LEFT  |  left key  |
| RIGHT  |  right key  |
| START  | space bar  |
| SELECT  | b  |
| SHUTDOWN  | q  |


## Working games
- tetris
- battle city
- shangay
- Dr.Mario (only some sprites move too fast, but fully playable)
- harmony
- serpent
- Q Billion

## Not fully working games
- space invaders is too fast
- pop up is a bit slow

## TO DO
- Implement ROM and RAM banking to support ROMs larger than 32kB
- Implement sound emulation
- Try new games
- Find new bugs


## SDL 2 
It requires SDL_2 library for graphic, timing, and inputs from keyboard - [link](https://www.libsdl.org/)

For Windows users this library is already present in the ./SDL2 folder of this project

For Linux users:
- Using apt-get `sudo apt-get install libsdl2-dev`
- From [source](https://www.libsdl.org/download-2.0.php). Then `./configure`, `make all` and `sudo make install` 

## Build
run `make gameboy` from both Linux and Windows inside the main directory

## Usage
Put the rom in the `roms` folder.

Move to the `GBpp-Emulator` folder, then `./gameboy gameboy_rom.gb` for Linux or `.\gameboy.exe gameboy_rom.gb` for Windows
 
 ## Screenshots
 <img src="https://github.com/linofex/GBpp-Emulator/blob/master/screenshots/boot.gif" height="200" width="200"> <img src="https://github.com/linofex/GBpp-Emulator/blob/master/screenshots/battle_city.png" height="200" width="200"> 
 
<img src="https://github.com/linofex/GBpp-Emulator/blob/master/screenshots/tetris.png" height="200" width="200"> <img src="https://github.com/linofex/GBpp-Emulator/blob/master/screenshots/tetris.gif" height="200" width="200">  

## Contributors
Fabio Condomitti - [@fcondo](https://github.com/fcondo)

Alessandro Noferi - [@linofex](https://github.com/linofex)
 
