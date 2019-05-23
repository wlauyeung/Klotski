#include "entity.h"

Entity::Entity(Model* model, float x, float y, float scaleX, float scaleY, int isClickable, const char* filePath) {
	this->model = model;
	this->x = x;
	this->y = y;
	this->scaleX = scaleX;
	this->scaleY = scaleY;
	this->filePath = filePath;
	clickable = isClickable;
	entityTex = new Texture(filePath);
	entityTex->mipmapping();
}

Entity::~Entity(void) {
	delete entityTex;
}

float Entity::getX() {
	return x;
}

float Entity::getY() {
	return y;
}

float Entity::getScaleX() {
	return scaleX;
}

float Entity::getScaleY() {
	return scaleY;
}

const char* Entity::getFilePath(){
	return filePath;
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

void Entity::setScaleX(float scaleX) {
	this->scaleX = scaleX;
}

void Entity::setScaleY(float scaleY) {
	this->scaleY = scaleY;
}

void Entity::move(float x, float y) {
	this->x += x;
	this->y += y;
}

GLuint Entity::getTextureID() {
	return entityTex->getTextureID();
}

int Entity::isClickable() {
	return clickable;
}