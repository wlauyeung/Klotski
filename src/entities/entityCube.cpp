#include "entityCube.h"

EntityCube::EntityCube(int x, int y, int z, float rotX, float rotY, float rotZ,
	int width, int height, int depth) :
	Entity(Model::CUBE, (float)x, (float)y, (float)z,
		(float)rotX, (float)rotY, (float)rotZ,
		(float)width, (float)height, (float)depth) {
}

EntityCube::EntityCube(int x, int z, int width, int depth) :
	Entity(Model::CUBE, (float)x, 0.0f, (float)z,
		0.0f, 0.0f, 0.0f, (float)width, 1.0f, (float)depth) {
}