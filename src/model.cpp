#include "model.h"

Model::Model(float vertices[], const int size) {
	this->vertices = vertices;
	this->size = size;
}

Model::~Model(void) {
}

float* Model::getVertices() {
	return vertices;
}

int Model::getSize() {
	return size;
}

void Model::draw() {

}
