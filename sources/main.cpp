#include <iostream>
#include "game.h"

int main(void){
	Game* game = new Game();
	game->Play();
	delete game;
	return 0;
}
