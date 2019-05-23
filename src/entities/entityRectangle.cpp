#include "entityRectangle.h"

EntityRectangle::EntityRectangle(int x, int y, int width, int height, int isClickable, const char* filePath) :
	Entity(Model::RECTANGLE, (float)x, (float)y, (float)
		(float)width, (float)height, isClickable, filePath) {

}

void EntityRectangle::action() {
}
