#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "model.h"

using namespace std;

class Graphics {

public:
	Graphics(GLFWwindow*& window, Model*& model);
	~Graphics(void);

	int genBuffer(void);
	void storeBufferData(GLfloat data[], int size);
	void render(void);

private:
	GLFWwindow* window;
	GLuint renderingProgram;
	GLuint vao;
	GLuint vbo;
	GLuint mvLoc, projLoc;
	int width, height;
	float cameraX, cameraY, cameraZ;
	float aspect;
	glm::mat4 pMat, vMat, mMat, mvMat;

	GLuint loadShader(int shaderTYPE, const char* filePath);
	GLuint createShaderProgram(const char* vp, const char* fp);
	int finalizeShaderProgram(GLuint sprogram);
	bool checkOpenGLError(void);
	void printProgramLog(int prog);

	Model* model;
};


#endif
