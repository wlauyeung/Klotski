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
#include "entities/entity.h"

using namespace std;

class Graphics {

public:
	Graphics(GLFWwindow* window);
	~Graphics(void);

	void render(Entity& e);
	void storeBufferData(GLfloat data[], int size, GLuint vboID);
	static GLuint genBuffer(void);
private:
	static std::vector<GLuint> vaos;
	static std::vector<GLuint> vbos;

	GLuint renderingProgram;
	GLuint mvLoc, projLoc;
	int width, height;
	float cameraX, cameraY, cameraZ;
	float aspect;
	glm::mat4 pMat, vMat, mMat, mvMat, tMat, rMat, sMat;
	GLuint loadShader(int shaderTYPE, const char* filePath);
	GLuint createShaderProgram(const char* vp, const char* fp);
	int finalizeShaderProgram(GLuint sprogram);
	bool checkOpenGLError(void);
	void printProgramLog(int prog);

};

#endif
