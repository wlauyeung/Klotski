#include "entityExitButton.h"

EntityExitButton::EntityExitButton(int x, int y, int width, int height, const char* filePath) :
	EntityRectangle((float)x, (float)y, (float)width, (float)height, 1, filePath) {
}

void EntityExitButton::action() {
	Game::getIntance()->stop();
}