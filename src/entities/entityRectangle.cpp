#include "entityRectangle.h"

EntityRectangle::EntityRectangle(int x, int y, int width, int height, const Color& color, int isButton) :
	Entity(Model::RECTANGLE, (float)x, (float)y, (float)
		(float)width, (float)height, color) {

	button = isButton;
}

int EntityRectangle::isButton() {
	return button;
}

void EntityRectangle::action() {
	//Do whatever here
}
