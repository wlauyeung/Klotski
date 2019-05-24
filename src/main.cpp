#include "game.h"
#include <windows.h>

int main() {
	FreeConsole();
	Game* game = new Game(460, 720);
	Game::setInstance(game);
	Game::getIntance()->start();
	return 0;
}