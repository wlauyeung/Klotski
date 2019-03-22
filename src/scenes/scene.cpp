#include "scene.h"

Scene::Scene() {};

std::vector<Entity*>& Scene::getEntities() {
	return entities;
}
