#include "game.h"

int main() {
	Game* game = new Game(460, 720);
	Game::setInstance(game);
	Game::getIntance()->start();
	return 0;
}