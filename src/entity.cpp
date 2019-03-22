#include "entity.h"

Entity::Entity(Model* model, float x, float y, float z, float rotX, float rotY, float rotZ) {
	this->model = model;
	this->x = x;
	this->y = y;
	this->z = z;
	this->rotX = rotX;
	this->rotY = rotY;
	this->rotZ = rotZ;
}

Entity::Entity(Model* model, float x, float y, float z) {
	this->model = model;
	this->x = x;
	this->y = y;
	this->z = z;
	this->rotX = 0.0f;
	this->rotY = 0.0f;
	this->rotZ = 0.0f;
}

Entity::~Entity(void) {}

float Entity::getX() {
	return x;
}

float Entity::getY() {
	return y;
}

float Entity::getZ() {
	return z;
}

float Entity::getRotX() {
	return rotX;
}

float Entity::getRotY() {
	return rotY;
}

float Entity::getRotZ() {
	return rotZ;
}

Model& Entity::getModel() {
	return *model;
}

void Entity::setX(float x) {
	this->x = x;
}

void Entity::setY(float y) {
	this->y = y;
}

void Entity::Entity::setZ(float z) {
	this->z = z;
}

void Entity::setRotX(float rotX) {
	this->rotX = rotX;
}

void Entity::setRotY(float rotY) {
	this->rotY = rotY;
}

void Entity::setRotZ(float rotZ) {
	this->rotZ = rotZ;
}

