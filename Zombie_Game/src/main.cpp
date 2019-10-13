//============================================================================
// Name        : videoGameProject.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <SDL2/SDL.h>
#include "Game.h"
//#include "leaker.h"
using namespace std;

const int width = 640;
const int height = 480;

Game* zombie=NULL;

int main() {

	const int FPS = 120;
	const int frameDelay =1000/FPS;

	Uint32 frameStart;
	int frameTime;
	zombie = new Game;


	zombie->init("Zombie Massacre", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, width, height, false);

	while(zombie->isRunning())
	{
		frameStart=SDL_GetTicks();

		zombie->handleEvents();
		zombie->update();
		zombie->render();

		frameTime = SDL_GetTicks()-frameStart;
		if(frameDelay>frameTime)
		{
			SDL_Delay(frameDelay-frameTime);
		}
	}

	zombie->clean();
	return 0;
}
