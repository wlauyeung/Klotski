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
#include "model.h"

using namespace std;

class Graphics {

public:
	static void init(GLFWwindow* window);
	static void destroy(void);

	static void render(Entity& e);
	static GLuint storeBufferData(int attribNumber, GLfloat data[], int size, int dim);

	static GLuint genVAO(float* vertices, int size, float* colorCoords, int colorSize);
private:
	static std::vector<GLuint> vaos;
	static std::vector<GLuint> vbos;
	static std::vector<int> attribs;
	static GLuint renderingProgram;
	static GLuint mLoc, projLoc;
	static int width, height;
	static glm::mat4 pMat, mMat, tMat, sMat;

	static GLuint loadShader(int shaderTYPE, const char* filePath);
	static GLuint createShaderProgram(const char* vp, const char* fp);
	static int finalizeShaderProgram(GLuint sprogram);
	static bool checkOpenGLError(void);
	static void printProgramLog(int prog);
	static void enableVertexAttribArrays(void);
	static void disableVertexAttribArrays(void);
};

#endif
