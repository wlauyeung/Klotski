#include "entityUndoButton.h"

EntityUndoButton::EntityUndoButton(int x, int y, int width, int height, const char* filePath) : 
	EntityRectangle((float)x, (float)y, (float)width, (float)height, 1, filePath) {
}

void EntityUndoButton::action() {
	//std::cout << "Undo!\n";
}

/*
	void EntityUndoButton::action(std::vector<std::vector<Entity*> >& stack) {
	std::cout << "Undo!\n";
	std::vector<Entity*> currentScene;
	std::vector<Entity*> previousScene;
	currentScene = stack.back();
	stack.pop_back();
	previousScene = stack.back();


	*for (Entity* ce : currentScene) {
		for (Entity* pe : previousScene) {
			move((int)(pe->getX()) - (int)(ce->getX()), (int)(pe->getY()) - (int)(ce->getY()));
		}
	}*/


