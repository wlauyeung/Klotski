#include "sceneTitle.h"

SceneTitle::SceneTitle() {
}

SceneTitle::~SceneTitle() {
	for (Entity* e : getEntities()) {
		delete e;
	}
}

void SceneTitle::load() {
	getEntities().push_back(new Entity(Model::CUBE, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f));
	getEntities().push_back(new Entity(Model::PYRAMID, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f));
	getEntities().push_back(new Entity(Model::PYRAMID, -2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f));
	getEntities().push_back(new Entity(Model::RECTANGLE, -5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f));
	getEntities().push_back(new Entity(Model::RECTANGLE, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f));
}

void SceneTitle::unload() {

}
