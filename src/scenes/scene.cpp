#include "scene.h"

Scene::Scene() {};

void Scene::setEntities(std::vector<Entity*> vec) {
	entities = vec;
}
std::vector<Entity*>& Scene::getEntities() {
	return entities;
}
