#include "game.h"

int main() {
	Game* game = new Game(1280, 720);
	Game::setInstance(game);
	Game::getIntance()->start();
	return 0;
}