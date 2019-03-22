#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

class Model {
public: 
	Model(float* vertices, const int size, const GLuint vboID);
	~Model(void);
	static Model* CUBE; 
	static Model* PYRAMID;
	static Model* RECTANGLE;

	static void deleteModels(void);
	static std::vector<Model*>& getModels(void);

	float* getVertices(void);
	int getSize(void);
	GLuint getVBOID(void);

	void setVBOID(GLuint vboID);

	
private:
	float* vertices;
	int size;
	GLuint vboID;

	static std::vector<Model*> models;
};

#endif