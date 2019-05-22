#include "entityUndoButton.h"

EntityUndoButton::EntityUndoButton(int x, int y, int width, int height, const Color & color, const char* filePath) : 
	EntityRectangle((float)x, (float)y, (float)width, (float)height, color, 1, filePath) {
}

void EntityUndoButton::action() {
}


