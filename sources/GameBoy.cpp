#include "../includes/GameBoy.hpp"
#include <vector>
#include <unistd.h>
#include <iostream>
#include <iomanip>

//#include <windows.h>

// /GameBoy::GameBoy(){}
GameBoy::GameBoy(std::string t_RomFileName):memory(), cpu(&memory), ppu(&memory), lcd(&memory, &ppu), rom(t_RomFileName), timer(&memory){ 
	// Bytes for ROM testing
    testRom = std::vector<BYTE> {0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 0x03, 0x73,
                        		 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D, 0x00, 0x08, 0x11, 0x1F, 
                        		 0x88, 0x89, 0x00, 0x0E, 0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 
                       			 0xD9, 0x99, 0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC, 
                       			 0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E
    							};
    memory.linkTimer(&timer);
	hostOldTime = SDL_GetPerformanceCounter();
	hostFrequency = SDL_GetPerformanceFrequency();
	accumulator = 0.0;
	initSDL();
}


// If a key is pressed this method requests a JOYPAD interrupt if necessary 
void GameBoy::pressedKey(BYTE t_key){
	BYTE keystatus = memory.getJoypadStatus();
    if(keystatus & (1 << t_key)){ // status is 1 and goes to 0
        keystatus &= ~(1 << t_key);
        InterruptHandler::requestInterrupt(&memory, JOYPAD);
	}
	memory.setJoypadStatus(keystatus);
}

// If a key is released this method reset the joypadstatus putting the bit at 1
void GameBoy::releasedKey(BYTE t_key){
	memory.setJoypadStatus(memory.getJoypadStatus() | (1 << t_key));
}

// This method gets user inputs
void GameBoy::userInput() {
	//while((SDL_PollEvent(&e)) != 0) {
	SDL_PumpEvents(); //This should only be run in the thread that sets the video mode.

	if(keyState[SDL_SCANCODE_Q]) {
		turnOff();
	}
	if(keyState[SDL_SCANCODE_SPACE]) {
		pressedKey(START);
	}
	if(keyState[SDL_SCANCODE_B]) {
		pressedKey(SELECT);
	}
	if(keyState[SDL_SCANCODE_S]) {
		pressedKey(_B);
	}
	if(keyState[SDL_SCANCODE_A]) {
		pressedKey(_A);
	}
	if(keyState[SDL_SCANCODE_DOWN]) {
		pressedKey(DOWN);	
	}
	if(keyState[SDL_SCANCODE_UP]) {
		pressedKey(UP);
	}
	if(keyState[SDL_SCANCODE_LEFT]) {
		pressedKey(LEFT);
	}
	if(keyState[SDL_SCANCODE_RIGHT]) {
		pressedKey(RIGHT);
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

    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	keyState = SDL_GetKeyboardState(NULL);
	return;
}

// This method loads the game in the ROM memory if all checks are correct
bool GameBoy::loadGame(){
	if(!rom.loadRom()){return false;}
	if(checkCartridge()){
		const std::vector<BYTE> *game = rom.getRom();

		//std::vector<BYTE>::const_iterator it = game->begin();

		//copy the rom in the the memory
	
		if(game->size() > 0x8000){
			std::cerr<< "Not enough memory";
			return false;
		}
		memory.loadROM(game);
		if(isTetris) memory.writeByte(0x02F0, 0x76);
		// for(; it != (*game).end() ; ++it){
		// 	if(address < 0x8000){
		// 		if(isTetris && address == 0x2F0){
		// 			memory.writeByte(address++, 0x76);
		// 		}		
		// 		else{memory.writeByte(address++, *it);}
		// 	}
		// 	else{
		// 		std::cerr<< "Not enough memory";
		// 		return false;
		// 	}
		// }
		memory.setReadOnlyRom();
		return true;
	}  
	return false;
}

void GameBoy::boot(){
	memory.setBootPhase();
}

void GameBoy::playGame(){
	for(;;){
		userInput(); 

		// REFRESH_CLOCKS_CYCLE = 70224 is the number of cycles before a lcd refresh
		while (cpu.getClockCycles() < REFRESH_CLOCKS_CYCLE){
			BYTE instructionCycles = cpu.step();
			cpu.addClockCycles(instructionCycles);
			lcd.step(instructionCycles);
			timer.updateTimers(instructionCycles);
			InterruptHandler::doInterrupt(&memory, &cpu);
		}

		// refresh the screen evey 70224 == 1/60s
		lcd.renderScreen(renderer, texture);
		// synchronize the two machines
		sync();
		cpu.resetClockCycles();
	}
}

// This method return if the first byte of the ROM are the same as the test Bytes
bool GameBoy::checkCartridge(){
    return rom.getNintendoLogo() == testRom;
}

void GameBoy::turnOff(){
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_DestroyTexture(texture);
	SDL_Quit();
	exit(1);
}


// This method emulates the timing of the gameboy.
// Since the host machine is faster than target machines, a sleep time
// syncronizes the machines


// void GameBoy::sync(){
// 	float c = cpu.getClockCycles();
// 	float time = c/4194304;
// 	std::cerr << "ETIME: " << time << "\n";
// 	std::cerr << "diffe: " << (float)SDL_GetTicks()/1000 - hostOldTime  << "\n";

// 	if(((float)SDL_GetTicks()/1000 - hostOldTime) < time){
// 		std::cerr << "ETIME: " << (time - (SDL_GetTicks()/1000 - hostOldTime))*1000000 << "\n";
// 		usleep((time - (SDL_GetTicks()/1000 - hostOldTime))*1000000);
// 		//hostOldTime = (float)SDL_GetTicks()/1000;
// 	}
// 	// double elapsedTime =   (double)(SDL_GetPerformanceCounter() - hostOldTime) / (double)hostFrequency;
// 	// if(elapsedTime < (double)1/60){
// 	// 	//std::cerr << "ETIME: " << elapsedTime << "\n";
// 	// 	useconds_t t  = ((double)1/60 - elapsedTime)*1000*1000;
// 	// 	accumulator += (((double)1/60 - elapsedTime)*1000*1000) - t;
// 	// 	//std::cerr << accumulator << "\n";
// 	// 	if(accumulator > 100){t+= accumulator;accumulator = 0.0;}
// 	// 	usleep(t);
		
// 	//}
// 	//else{std::cerr << "ELSE: " << elapsedTime << "\n";}
// 	hostOldTime = (float)SDL_GetTicks()/1000;

	
// }




// This method emulates the timing of the gameboy.
// Since the host machine is faster than target machines, a sleep time
// syncronizes the machines

void GameBoy::sync(){
	double elapsedTime =  (double)(SDL_GetPerformanceCounter() - hostOldTime) / (double)hostFrequency;
	if(elapsedTime < REFRESH_RATE){
		
		useconds_t t  = (REFRESH_RATE - elapsedTime)*1000*1000;
		if((t - accumulator) > 0){
			usleep(t-accumulator);
			accumulator = 0.0;
		}
		else{
			accumulator = ((accumulator - t) < 0) ? 0 : accumulator - t; 
		}
	}
	else{
		if(!memory.isBooting()){
			
			accumulator += (elapsedTime - REFRESH_RATE)*1000*1000;
		}
	}
	hostOldTime = SDL_GetPerformanceCounter();
	
}

GameBoy::~GameBoy(){
    //std::cout << "GAMEBOY distruttore\n";
}