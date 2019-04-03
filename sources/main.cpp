//#include "../includes/rom.hpp"
//#include "../includes/memory.hpp"
#include "../includes/GameBoy.hpp"
//#include "../includes/cpu.hpp"
//using namespace GBemulator;
int main(int argc, char** argv){

    WINDOW* window;

    int startx, starty;
	int h, w;
	initscr();	// init routine. Must be called first
	cbreak();	// buffering disbling
	keypad(stdscr, TRUE); // for arrow keys
	starty = (LINES - SCREEN_HEIGHT) / 2;
	startx = (COLS - SCREEN_WIDTH) / 2;
	 
	window = newwin(144, 320, 0, 0);
	refresh();
	box(window, '*' , '*');
	wprintw(window, "DIO CANE");
	wrefresh(window);

getch();


    // if (argc == 2){
    //     std::string romName = "./roms/" + std::string(argv[1]);
    //     GameBoy gameboy = GameBoy(romName);
    //     getch();
    //     if(gameboy.loadGame())
    //         //gameboy.playGame();
    //     std::cout << "QUI\n";
    //     //gameboy.PrintByte(0x0134);
    // }
    // std::cout<< "anche QUA\n";
            

} 