#include "entityUndoButton.h"

EntityUndoButton::EntityUndoButton(int x, int y, int width, int height, const char* filePath) : 
	EntityRectangle((float)x, (float)y, (float)width, (float)height, 1, filePath) {
}

void EntityUndoButton::action() {
	std::cout << "Undo!\n";	
}


