#include <SDL2/SDL.h>
#include "Game.h"
#include <iostream>

Game game;

int main(int argc, char **argv) {
	game.init();

	while(game.isRunning()) {
		game.mainLoop();
	}

	SDL_Quit();

	return 0;
}
