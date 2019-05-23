#include "entityRectangle.h"

EntityRectangle::EntityRectangle(int x, int y, int width, int height, int isButton, const char* filePath) :
	Entity(Model::RECTANGLE, (float)x, (float)y, (float)
		(float)width, (float)height, filePath) {

	button = isButton;
}

int EntityRectangle::isButton() {
	return button;
}

void EntityRectangle::action() {
	//Do whatever here
}
