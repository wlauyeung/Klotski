#include "sceneTitle.h"

SceneTitle::SceneTitle() {
}

SceneTitle::~SceneTitle() {
	for (Entity* e : getEntities()) {
		delete e;
	}
}

void SceneTitle::load() {
	getEntities().push_back(new EntityRectangle(570, 160, 140, 140, 0, "red.jpg")); //center 2x2
	getEntities().push_back(new EntityRectangle(500, 160, 70, 140, 0, "green.jpg")); // top 1x2 left
	getEntities().push_back(new EntityRectangle(710, 160, 70, 140, 0, "green.jpg")); // top 1x2 right
	getEntities().push_back(new EntityRectangle(500, 300, 70, 140, 0, "green.jpg")); // mid 1x2 left
	getEntities().push_back(new EntityRectangle(710, 300, 70, 140, 0, "green.jpg")); // mid 1x2 right
	getEntities().push_back(new EntityRectangle(570, 300, 140, 70, 0, "yellow.jpg")); // mid 2x1
	getEntities().push_back(new EntityRectangle(570, 370, 70, 70, 0, "blue.jpg")); // mid 1x1 left
	getEntities().push_back(new EntityRectangle(640, 370, 70, 70, 0, "blue.jpg")); // mid 1x1 right
	getEntities().push_back(new EntityRectangle(500, 440, 70, 70, 0, "blue.jpg")); // bottom 1x1 left
	getEntities().push_back(new EntityRectangle(710, 440, 70, 70, 0, "blue.jpg")); // bottom 1x1 right
	getEntities().push_back(new EntityUndoButton(100, 160, 140, 70, "blue.jpg")); // undo button
	getEntities().push_back(new EntityRectangle(100, 240, 140, 70, 1, "blue.jpg")); // undo button
}

void SceneTitle::unload() {

}
