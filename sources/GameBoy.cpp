#include "../includes/GameBoy.hpp"
#include <vector>
#include <unistd.h>
#include <iostream>
#include <iomanip>

//#include <windows.h>

// /GameBoy::GameBoy(){}
GameBoy::GameBoy(std::string t_RomFileName):memory(), cpu(&memory), ppu(&memory), lcd(&memory, &ppu), rom(t_RomFileName), timer(&memory), times(8,0){ 
	// Bytes for ROM testing
    testRom = std::vector<BYTE> {0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 0x03, 0x73,
                        		 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D, 0x00, 0x08, 0x11, 0x1F, 
                        		 0x88, 0x89, 0x00, 0x0E, 0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 
                       			 0xD9, 0x99, 0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC, 
                       			 0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E
    							};
	
    memory.linkTimer(&timer);
	targetOldTime = (double)(1000.0*cpu.getClockCycles())/(4194304); //TARGETPERIOD * 0; // 0
	hostOldTime = SDL_GetPerformanceCounter();
	hostFrequency = SDL_GetPerformanceFrequency();
	displayTime = SDL_GetTicks();
	accumulator = 0.0;
	initSDL();
	o = 0;
}


// If a key is pressed this method requests a JOYPAD interrupt if necessary 
void GameBoy::pressedKey(BYTE t_key){
	BYTE keystatus = memory.getJoypadStatus();
	//BYTE joypadStatus = memory.readf();
	    // if ~ 0(pressed) && time expired
    /* if(!(keystatus & (1 << t_key)) && SDL_GetTicks() - times[t_key] > PRESSION_DURATION/50){
        keystatus |= (1 << t_key);
    }
    else  */if(keystatus & (1 << t_key)){ // status is 1 and goes to 0
        keystatus &= ~(1 << t_key);
       // if((t_key > 3 && !(joypadStatus & BUTTON) == 0x10) || (t_key < 4 && !(joypadStatus & DIRECTION)==0x20)){
            InterruptHandler::requestInterrupt(&memory, JOYPAD);
			times[t_key] = SDL_GetTicks(); //start pression time
        //}
    }
	memory.setJoypadStatus(keystatus);

}
// If a key is released this method reset the joypadstatus putting the bit at 1
void GameBoy::releasedKey(BYTE t_key){
	/* BYTE keystatus = memory.getJoypadStatus();
    if(!(keystatus & (1 << t_key)) && SDL_GetTicks() - times[t_key] > PRESSION_DURATION/50){
		std::cout << " TOLTOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n";
        keystatus |= (1 << t_key);
    }  */
	memory.setJoypadStatus(memory.getJoypadStatus() | (1 << t_key));
}

// This method gets user inputs
void GameBoy::userInput() {
	SDL_Event e;
	SDL_PumpEvents(); //faster with this or with wwhile((SDL_PollEvent(&e)) != 0)??
	//while((SDL_PollEvent(&e)) != 0) {
		if(keyState[SDL_SCANCODE_Q]) {
			//std::cout << "OFF"<< std::endl;
			turnOff();
		}
		if(keyState[SDL_SCANCODE_SPACE]) {
			pressedKey(START);
			//std::cout << "START"<< std::endl;
		}
		if(keyState[SDL_SCANCODE_B]) {
			pressedKey(SELECT);
			//std::cout << "SELECT"<< std::endl;
		}
		if(keyState[SDL_SCANCODE_S]) {
			pressedKey(_B);
			//std::cout << "B"<< std::endl;
		}
		if(keyState[SDL_SCANCODE_A]) {
			pressedKey(_A);
			//std::cout << "A"<< std::endl;
		}
		if(keyState[SDL_SCANCODE_DOWN]) {
			pressedKey(DOWN);	
			//std::cout << "DOWN"<< std::endl;
		}
		if(keyState[SDL_SCANCODE_UP]) {
			pressedKey(UP);
			//std::cout << "UP"<< std::endl;
		}
		if(keyState[SDL_SCANCODE_LEFT]) {
			pressedKey(LEFT);
			//std::cout << "LEFT"<< std::endl;
		}
		if(keyState[SDL_SCANCODE_RIGHT]) {
			pressedKey(RIGHT);
			//std::cout << "RIGHT"<< std::endl;
		}

		if(!keyState[SDL_SCANCODE_SPACE]) {
			releasedKey(START);	
		}
		if(!keyState[SDL_SCANCODE_B]) {
			releasedKey(SELECT);
		}
		if(!keyState[SDL_SCANCODE_S]) {
			releasedKey(_B);
		}
		if(!keyState[SDL_SCANCODE_A]) {
			releasedKey(_A);
		}
		if(!keyState[SDL_SCANCODE_DOWN]) {
			releasedKey(DOWN);	
		}
		if(!keyState[SDL_SCANCODE_UP]) {
			releasedKey(UP);
		}
		if(!keyState[SDL_SCANCODE_LEFT]) {
			releasedKey(LEFT);
		}
		if(!keyState[SDL_SCANCODE_RIGHT]) {
			releasedKey(RIGHT);
		}
	//} 
}

void GameBoy::initSDL(){
    SDL_Init(SDL_INIT_VIDEO);

	//get the current display resolution
	SDL_DisplayMode current;
	int result = SDL_GetCurrentDisplayMode(0, &current);
	if(result != 0) {
		//SDL_Log("Could not get display mode for video display #%d: %s", SDL_GetError());
	}
	else {
		//SDL_Log("Display #%d: current display mode is %dx%dpx @ %dhz.", current.w, current.h, current.refresh_rate);
	}
	//scaling keeps the ratio 160/144
	int sizeX = current.w/2;// - 800;
	int sizeY = sizeX*SCREEN_HEIGHT/SCREEN_WIDTH;
	//std::cerr<<"Display size is "<<sizeX<<"x"<<sizeY<<"px\n";
	
	//SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
	window = SDL_CreateWindow("Gbb-Emulator",
                        SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED, 
						sizeX, sizeY, 
                        //WINDOW_WIDTH,WINDOW_HEIGHT,
                        0);

    /* We must call SDL_CreateRenderer in order for draw calls to affect this window. */
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

	texture = SDL_CreateTexture(renderer,
								SDL_PIXELFORMAT_RGB888,
								SDL_TEXTUREACCESS_STREAMING, 
								SCREEN_WIDTH,
								SCREEN_HEIGHT);
								
	//SDL_Log("Display #%d: new display mode is %dx%dpx @ %dhz.", sizeX, sizeY, current.refresh_rate);

	//SDL_RenderSetScale(renderer, 160,144);

    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_SetRenderDrawColor(renderer, 23, 120, 32, 0);
    SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	keyState = SDL_GetKeyboardState(NULL);

	return;
}

// This method loads the game in the ROM memory if all checks are correct
bool GameBoy::loadGame(){
	if(checkCartridge()){
		const std::vector<BYTE> *game = rom.getRom();
		WORD address = 0x0000;
		std::vector<BYTE>::const_iterator it = game->begin();
		int counter = 0;
		for(; it != (*game).end() ; ++it){
			if(address < 0x8000){
				if(isTetris && address == 0x2F0){
					memory.writeByte(address++, 0x76);
				}		
				else{memory.writeByte(address++, *it);}
			}
			else{
				std::cerr<< "Not enough memory";
				return false;
			}
		}
		memory.setReadOnlyRom();
		return true;
	}  
	return false;
}

void GameBoy::playGame(){
	//WORD pp = 0x101;
	//std::cerr << "dammi un pc: ";
	//std::cin >> std::hex >> pp;
	//cpu.reset();
	bool flag = false;

	for(;;){
		userInput();
		BYTE instructionCycles = cpu.step();
		//instructionCycles *=2;
		lcd.step(instructionCycles);
		// }	 	

		
		cpu.addClockCycle(instructionCycles);
		if(InterruptHandler::doInterrupt(&memory, &cpu)){
			lcd.renderScreen(renderer, texture);
			sync();
		}
		timer.updateTimers(instructionCycles);
		// sync();
		//std::cerr << o++ << " ";
		//std::cout<< o++ << "  ";
		//std::cerr << std::hex << (int)cpu.getPC()<< " - ";
		//if(cpu.getPC() == 0x26f){
		//if(++o == 269596 ) { //|| flag == true){
		
		// //	flag = true;
		// //	flag = false;
		// 	std::string pp;
		// 	//ppu.fillLineOfTileDB(0x8010);
		// 	//getchar();	
		 //	cpu.printCpuState();
		//	getchar();
		//}
		// // 	//system("PAUSE");
		// 	//sstd::cerr <<"\npop6: "<<std::hex <<(int)cpu.readByte(0xFFFF);
		// 	std::cerr <<"metti pc: ";
		// 	std::cin >> std::hex >> pp;
		// }
	
//getchar();			// //std::cerr << " BOOM " << o;
			// //std::cerr << (int)cpu.getPC();
		//}
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

void GameBoy::turnOff(){
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	exit(1);
}


// This method emulates the timing of the gameboy.
// Since the host machine is faster than target machines, a sleep time
// syncronizes the machines


void GameBoy::sync(){
	double elapsedTime =   (double)(SDL_GetPerformanceCounter() - hostOldTime) / (double)hostFrequency;
	
	if(elapsedTime < (double)1/60){
		//std::cerr << elapsedTime << "\n";
		useconds_t t  = ((double)1/60 - elapsedTime)*1000*1000;
		accumulator += (((double)1/60 - elapsedTime)*1000*1000) - t;
		//std::cerr << accumulator << "\n";
		if(accumulator > 100){t+= accumulator;accumulator = 0.0;}
		usleep(t);
	}
	hostOldTime = SDL_GetPerformanceCounter();
}

// void GameBoy::sync(){

// 	Uint64 hostNewTime = SDL_GetPerformanceCounter();
// 	double hostElapsedTime = (double)(hostNewTime - hostOldTime) / (double)(hostFrequency);
 	
//     double targetNewTime = (double)(1000.0*cpu.getClockCycles())/(4194304);
//     double targetElapsedTime = targetNewTime - targetOldTime;
	
// 	//std::cout<<"Clock cycles: "<<'\t'<<cpu.getClockCycles()<<std::endl;
// 	//std::cout<<"The host elapsed time is: "<<'\t'<<(double)hostElapsedTime<<std::endl;
// 	//std::cout<<"The host elapsed time is: "<<'\t'<<hostNewTime<<std::endl;
// 	//std::cout<<"The target elapsed time is: "<<'\t'<<targetElapsedTime<<std::endl;

// 	double timeDifference =  targetElapsedTime - hostElapsedTime;
// 	//std::cout<<"DIFF: "<<'\t'<< (double)(timeDifference)<<std::endl;    
		
//     if(timeDifference > 10) {    //2 ms
// 		//std::cerr<<"HITT!!  The diff is: "<<'\t'<< (long double)(timeDifference)<<std::endl;
// 	    //usleep(timeDifference*1000); // sleep 
// 		hostOldTime =  SDL_GetPerformanceCounter();
//    		targetOldTime = targetNewTime;//(double)(1000.0*cpu.getClockCycles())/(4194304);	
// 		/*std::cout<<"The host updated time: "<<'\t'<<hostOldTime<<std::endl;
// 		std::cout<<"The target updated time: "<<'\t'<<targetOldTime<<std::endl;*/
// 	}
// 	//else {
// 	//	//std::cerr<<"MISS!!  The diff is: "<<'\t'<< (float)(timeDifference)<<std::endl;
// 	//}
// }

GameBoy::~GameBoy(){
    //std::cout << "GAMEBOY distruttore\n";
}