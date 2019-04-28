#include "sceneTitle.h"

SceneTitle::SceneTitle() {
}

SceneTitle::~SceneTitle() {
	for (Entity* e : getEntities()) {
		delete e;
	}
}

void SceneTitle::load() {
	getEntities().push_back(new EntityCube(0, 0, 1, 2)); // most top left block
	getEntities().push_back(new EntityCube(1, 0, 2, 2)); // 2x2 block 
	getEntities().push_back(new EntityCube(3, 0, 1, 2)); // most top right block
	getEntities().push_back(new EntityCube(0, 2, 1, 2)); // middle left block
	getEntities().push_back(new EntityCube(3, 2, 1, 2)); // middle right block
	getEntities().push_back(new EntityCube(1, 2, 2, 1)); // 2x1 middle block
	getEntities().push_back(new EntityCube(1, 3, 1, 1)); // 1x1 middle left block
	getEntities().push_back(new EntityCube(2, 3, 1, 1)); // 1x1 middle right block
	getEntities().push_back(new EntityCube(0, 4, 1, 1)); // most bottom left block
	getEntities().push_back(new EntityCube(3, 4, 1, 1)); // most bottom right block
}

void SceneTitle::unload() {

}
