#include "model.h"

Model* Model::CUBE;
Model* Model::RECTANGLE;
std::vector<Model*> Model::models;

void Model::deleteModels() {
	for (Model* m : models) {
		delete m;
	}
}

std::vector<Model*>& Model::getModels() {
	return models;
}

Model::Model(float* vertices, const int size, const GLuint vboID) {
	this->vertices = vertices;
	this->size = size;
	this->vboID = vboID;
}

Model::~Model(void) {
	delete vertices;
}

float* Model::getVertices() {
	return vertices;
}

int Model::getSize() {
	return size;
}

GLuint Model::getVBOID() {
	return vboID;
}

void Model::setVBOID(GLuint vboID) {
	this->vboID = vboID;
}
