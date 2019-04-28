#include "entity.h"

Entity::Entity(Model* model, float x, float y, float z, float rotX, float rotY, float rotZ, 
	float scaleX, float scaleY, float scaleZ) {
	this->model = model;
	this->x = x;
	this->y = y;
	this->z = z;
	this->rotX = rotX;
	this->rotY = rotY;
	this->rotZ = rotZ;
	this->scaleX = scaleX;
	this->scaleY = scaleY;
	this->scaleZ = scaleZ;
}

Entity::Entity(Model* model, float x, float y, float z, float rotX, float rotY, float rotZ) {
	this->model = model;
	this->x = x;
	this->y = y;
	this->z = z;
	this->rotX = rotX;
	this->rotY = rotY;
	this->rotZ = rotZ;
	this->scaleX = 1.0f;
	this->scaleY = 1.0f;
	this->scaleZ = 1.0f;
}

Entity::Entity(Model* model, float x, float y, float z) {
	this->model = model;
	this->x = x;
	this->y = y;
	this->z = z;
	this->rotX = 0.0f;
	this->rotY = 0.0f;
	this->rotZ = 0.0f;
	this->scaleX = 1.0f;
	this->scaleY = 1.0f;
	this->scaleZ = 1.0f;
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

float Entity::getScaleX() {
	return scaleX;
}

float Entity::getScaleY() {
	return scaleY;
}

float Entity::getScaleZ() {
	return scaleZ;
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

void Entity::setScaleX(float scaleX) {
	this->scaleX = scaleX;
}

void Entity::setScaleY(float scaleY) {
	this->scaleY = scaleY;
}

void Entity::setScaleZ(float scaleZ) {
	this->scaleZ = scaleZ;
}


