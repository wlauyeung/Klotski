#include "sceneTitle.h"

SceneTitle::SceneTitle() {
}

SceneTitle::~SceneTitle() {
	for (Entity* e : getEntities()) {
		delete e;
	}
}

void SceneTitle::load() {
	getEntities().push_back(new EntityRectangle(65, 90, 300, 200, 0, "res/red.jpg")); //title
	getEntities().push_back(new EntityRectangle(430, 90, 420, 490, 0, "res/board.jpg")); //board
	getEntities().push_back(new EntityRectangle(570, 160, 140, 140, 1, "res/red.jpg")); //center 2x2
	getEntities().push_back(new EntityRectangle(500, 160, 70, 140, 1, "res/green.jpg")); // top 1x2 left
	getEntities().push_back(new EntityRectangle(710, 160, 70, 140, 1, "res/green.jpg")); // top 1x2 right
	getEntities().push_back(new EntityRectangle(500, 300, 70, 140, 1, "res/green.jpg")); // mid 1x2 left
	getEntities().push_back(new EntityRectangle(710, 300, 70, 140, 1, "res/green.jpg")); // mid 1x2 right
	getEntities().push_back(new EntityRectangle(570, 300, 140, 70, 1, "res/yellow.jpg")); // mid 2x1
	getEntities().push_back(new EntityRectangle(570, 370, 70, 70, 1, "res/blue.jpg")); // mid 1x1 left
	getEntities().push_back(new EntityRectangle(640, 370, 70, 70, 1, "res/blue.jpg")); // mid 1x1 right
	getEntities().push_back(new EntityRectangle(500, 440, 70, 70, 1, "res/blue.jpg")); // bottom 1x1 left
	getEntities().push_back(new EntityRectangle(710, 440, 70, 70, 1, "res/blue.jpg")); // bottom 1x1 right
	getEntities().push_back(new EntityUndoButton(150, 320, 140, 70, "res/undo.png")); // undo button
	getEntities().push_back(new EntityExitButton(150, 400, 140, 70, "res/exit.png")); // exit button
}

void SceneTitle::unload() {
	for (Entity* e : getEntities()) {
		delete e;
	}
}
