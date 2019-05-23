#include "sceneTitle.h"

SceneTitle::SceneTitle() {
}

SceneTitle::~SceneTitle() {
	for (Entity* e : getEntities()) {
		delete e;
	}
}

void SceneTitle::load() {
	getEntities().push_back(new EntityRectangle(30, 20, 400, 86, 0, "res/title.jpg")); //title
	getEntities().push_back(new EntityRectangle(20, 120, 420, 490, 0, "res/board.jpg")); //board
	getEntities().push_back(new EntityRectangle(160, 190, 140, 140, 1, "res/red.jpg")); //center 2x2
	getEntities().push_back(new EntityRectangle(90, 190, 70, 140, 1, "res/green.jpg")); // top 1x2 left
	getEntities().push_back(new EntityRectangle(300, 190, 70, 140, 1, "res/green.jpg")); // top 1x2 right
	getEntities().push_back(new EntityRectangle(90, 330, 70, 140, 1, "res/green.jpg")); // mid 1x2 left
	getEntities().push_back(new EntityRectangle(300, 330, 70, 140, 1, "res/green.jpg")); // mid 1x2 right
	getEntities().push_back(new EntityRectangle(160, 330, 140, 70, 1, "res/yellow.jpg")); // mid 2x1
	getEntities().push_back(new EntityRectangle(160, 400, 70, 70, 1, "res/blue.jpg")); // mid 1x1 left
	getEntities().push_back(new EntityRectangle(230, 400, 70, 70, 1, "res/blue.jpg")); // mid 1x1 right
	getEntities().push_back(new EntityRectangle(90, 470, 70, 70, 1, "res/blue.jpg")); // bottom 1x1 left
	getEntities().push_back(new EntityRectangle(300, 470, 70, 70, 1, "res/blue.jpg")); // bottom 1x1 right
	getEntities().push_back(new EntityUndoButton(60, 630, 140, 70, "res/undo.png")); // undo button
	getEntities().push_back(new EntityExitButton(260, 630, 140, 70, "res/exit.png")); // exit button
}

void SceneTitle::unload() {
	for (Entity* e : getEntities()) {
		delete e;
	}
}