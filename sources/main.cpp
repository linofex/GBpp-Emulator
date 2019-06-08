#include "../includes/GameBoy.hpp"
#include "../includes/utility.hpp"

 // used to run tetris faster
bool isTetris = false;

int main(int argc, char** argv){
    SDL_SetMainReady();
    if (argc == 2){
        std::string romName = "./roms/" + std::string(argv[1]);
        if (std::string(argv[1]) == "tetris.gb"){isTetris = true;}
        GameBoy gameboy = GameBoy(romName);
        gameboy.boot();
        if(gameboy.loadGame()){
            gameboy.playGame();
        }
        else{
            gameboy.turnOff();
        }
    }
    return 0;    

} 