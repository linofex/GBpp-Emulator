#include "../includes/GameBoy.hpp"
#include <vector>
#include <unistd.h>
#include <iostream>
// /GameBoy::GameBoy(){}
GameBoy::GameBoy(std::string t_RomFileName):memory(), cpu(&memory), ppu(&memory), lcd(&memory, &ppu), rom(t_RomFileName), timer(&memory), times(8,0){ 
	// Bytes for ROM testing
    testRom = std::vector<BYTE> {0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 0x03, 0x73,
                        		 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D, 0x00, 0x08, 0x11, 0x1F, 
                        		 0x88, 0x89, 0x00, 0x0E, 0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 
                       			 0xD9, 0x99, 0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC, 
                       			 0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E
    							};
	clockCycles = 0;
    targetOldTime = TARGETPERIOD * clockCycles; // 0
    hostOldTime = SDL_GetTicks(); //  millisecons

	displayTime = SDL_GetTicks();
	initSDL();
	o = 0;
}


// If a key is pressed this method requests a JOYPAD interrupt if necessary 
void GameBoy::pressedKey(int t_key){
	BYTE keystatus = memory.getJoypadStatus();
	BYTE joypadStatus = memory.readByte(0xFF00);
    // if ~ 0(pressed) && time expired
    if(!(keystatus & (1 << t_key)) && SDL_GetTicks() - times[t_key] > PRESSION_DURATION){
        keystatus |= (1 << t_key);
    }
    else if(keystatus & (1 << t_key)){ // status is 1 and goes to 0
        keystatus &= ~(1 << t_key);
        if((t_key > 3 && !(joypadStatus & BUTTON)) || (t_key < 4 && !(joypadStatus & DIRECTION))){
            InterruptHandler::requestInterrupt(&memory, JOYPAD);
			times[t_key] = SDL_GetTicks(); //start pression time
        }
    }
	memory.setJoypadStatus(joypadStatus);

}
// If a key is released this method reset the joypadstatus putting the bit at 1
void GameBoy::releasedKey(int t_key){
	memory.setJoypadStatus(memory.getJoypadStatus() | (1 << t_key));
}

// This method gets user inputs
void GameBoy::userInput() {
	SDL_PollEvent(&event);
	switch (event.type)	{
		case (SDL_QUIT):
			std::cerr << "QUO";
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			SDL_Quit();
			exit(1);
		case (SDL_KEYDOWN):
			switch (event.key.keysym.sym){
				case (SDLK_8):
					SDL_DestroyRenderer(renderer);
					SDL_DestroyWindow(window);
					SDL_Quit();
					exit(1);
					break;
				case(SDLK_RIGHT):
					pressedKey(RIGHT);
					break;
				case(SDLK_LEFT):
					pressedKey(LEFT);
					break;
				case(SDLK_UP):
					pressedKey(UP);
					break;
				case(SDLK_DOWN):
					pressedKey(DOWN);
					break;
				case(SDLK_a):		//a
					pressedKey(_A);
					break;
				case(SDLK_s): 		//b
					pressedKey(_B);
					break;
				case(SDLK_b): 		//select
					pressedKey(SELECT);
					break;
				case(SDLK_SPACE):	//start
					pressedKey(START);
					break;
				default:
					break;
			}

		case (SDL_KEYUP):
			switch (event.key.keysym.sym){
				case(SDLK_RIGHT):
					releasedKey(RIGHT);
					break;
				case(SDLK_LEFT):
					releasedKey(LEFT);
					break;
				case(SDLK_UP):
					releasedKey(UP);
					break;
				case(SDLK_DOWN):
					releasedKey(DOWN);
					break;
				case(SDLK_a):		//a
					releasedKey(_A);
					break;
				case(SDLK_s): 		//b
					releasedKey(_B);
					break;
				case(SDLK_b): 		//select
					releasedKey(SELECT);
					break;
				case(SDLK_SPACE):	//start
					releasedKey(START);
					break;
				default:
					break;
				}
	}
}

void GameBoy::initSDL(){
    SDL_Init(SDL_INIT_VIDEO);
    //SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
     window = SDL_CreateWindow("Gbb-Emulator",
                        SDL_WINDOWPOS_CENTERED -80, SDL_WINDOWPOS_CENTERED,
                        WINDOW_WIDTH,WINDOW_HEIGHT,
                        0);

        /* We must call SDL_CreateRenderer in order for draw calls to affect this window. */
        renderer = SDL_CreateRenderer(window, -1, 0);

	//SDL_RenderSetScale(renderer, 160,144);
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_SetRenderDrawColor(renderer, 0, 0, 254, 0);
    SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	return;
}


// This method loads the game in the ROM memory if all checks are correct
bool GameBoy::loadGame(){
	
	if(checkCartridge()){
		std::vector<BYTE> game(rom.getRom());
		WORD address = 0x0000;
		std::vector<BYTE>::iterator it = game.begin();
		for(; it != game.end() ; ++it){
			if(address <= 0x8000){
				memory.writeByte(address++, *it);
			}
			else{
				std::cerr<< "Not enough memory";
				return false;
			}
		}
		return true;
	}  
	return false;
}

void GameBoy::playGame(){
	for(;;){
		userInput();
		//std::cout<<"--------------------------------------------\n";

		BYTE instructionCycles = cpu.step();
		lcd.step(instructionCycles);
		
		if(SDL_GetTicks() - displayTime > 20){
			//lcd.renderScreen(window, renderer);
			displayTime = SDL_GetTicks();
		}//		
		clockCycles += instructionCycles;
		InterruptHandler::doInterrupt(&memory, &cpu);
		//sync();
		//std::cerr << o++ << " ";
		o++;
		if(cpu.getPC() == 0x2795){
			cpu.printCpuState();
			//std::cerr << " BOOM " << o;


			//std::cerr << (int)cpu.getPC();
			exit(1);
		}
	}
}

void GameBoy::printByte(WORD t_add){
    //std::cout << memory.readByte(t_add); 
}
void GameBoy::printNintendoGraphic(){
	rom.printNintendoGraphic();
	//std::cout<< "Nintendo Graphic: ";
	std::vector<BYTE>::const_iterator it = testRom.begin();
    for (; it != testRom.end(); ++it){//std::cout << std::hex << (unsigned int)*it << " ";}
    //std::cout << std::endl;
	}
}
void GameBoy::printRomInfo(){
	rom.printRomName();
	// rom.PrintRamSize();
	// rom.PrintRomSize();
	// rom.PrintCartridgeType();
	// rom.PrintColorType();
	// rom.PrintDestCode();
	// rom.PrintLicenseCodeOld();
	// rom.PrintLicenseCodeNew();
	rom.printNintendoGraphic();
	//rom.PrintBeginPoint();
}

// This method return if the first byte of the ROM are the same as the test Bytes
bool GameBoy::checkCartridge(){
    return rom.getNintendoLogo() == testRom;
}

// This method emulates the timing of the gameboy.
// Since the host machine is faster than target machines, a sleep time
// syncronizes the machines
void GameBoy::sync(){
	Uint32 hostNewTime = SDL_GetTicks();
    Uint32 hostElapsedTime = hostNewTime - hostOldTime;
	std::cerr<<"\nQQ "<<'\t'<< (float)(hostNewTime )<<std::endl;
	std::cerr<<"\nWW "<<'\t'<< (float)(hostOldTime)<<std::endl;
    //std::cout<<"The host elapsed time is: "<<'\t'<<hostElapsedTime<<std::endl;
 	
    float targetNewTime = TARGETPERIOD * clockCycles;
    float targetElapsedTime = targetNewTime - targetOldTime;
    //std::cout<<"The target elapsed time is: "<<'\t'<<targetElapsedTime<<std::endl;
    
	float_t timeDifference =  targetNewTime - hostNewTime;
	    
		
    // if(timeDifference > 5) {    //2 ms
	// 	std::cerr<<"HITT!!  The diff is: "<<'\t'<< (float)(timeDifference)<<std::endl;
    //     usleep(timeDifference*1000); // sleep 
	// 	hostOldTime = SDL_GetTicks();
   	// 	targetOldTime = targetNewTime;
		
	// }
	// else {
	// 	std::cerr<<"MISS!!  The diff is: "<<'\t'<< (float)(timeDifference)<<std::endl;

	// }
   
}

GameBoy::~GameBoy(){
    //std::cout << "GAMEBOY distruttore\n";
}