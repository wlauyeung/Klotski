#include "model.h"

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

Model::Model(float* vertices, const int verticesSize, float* colorCoords, const int colorSize, const int vaoID) {
	this->vaoID = vaoID;
	arrayList.push_back(vertices);
	sizeList.push_back(verticesSize);
	arrayList.push_back(colorCoords);
	sizeList.push_back(colorSize);
}

Model::~Model(void) {

}

float* Model::getVertices() {
	return arrayList.at(0);
}

int Model::getVerticesSize() {
	return sizeList.at(0);
}

GLuint Model::getVaoID(void) {
	return vaoID;
}
