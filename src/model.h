#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

class Model {
public:
	Model(float* vertices, const int verticesSize, float* colorCoords, const int colorSize, const int vaoID);
	~Model(void);
	static Model* RECTANGLE;

	static void deleteModels(void);
	static std::vector<Model*>& getModels(void);

	float* getVertices(void);
	int getVerticesSize(void);
	GLuint getVaoID(void);

private:
	std::vector<float*> arrayList;
	std::vector<int> sizeList;
	GLuint vaoID;

	static std::vector<Model*> models;
};

#endif