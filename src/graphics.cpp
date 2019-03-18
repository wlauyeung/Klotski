#include "graphics.h"

Graphics::Graphics(GLFWwindow*& window, Model*& model) {
	cameraX = 0.0f; cameraY = 0.0f; cameraZ = 8.0f;

	this->model = model;
	this->window = window;

	renderingProgram = createShaderProgram("shaders/vertShader.glsl", "shaders/fragShader.glsl");
	genBuffer();
	
	storeBufferData(model->getVertices(), model->getSize());
}

Graphics::~Graphics() {
	glDeleteBuffers(1, &vbo);
	glDeleteProgram(renderingProgram);

	delete model;
	delete this;
}

int Graphics::genBuffer() {
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	return 0;
}

void Graphics::storeBufferData(GLfloat data[], int size) {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(data), data, GL_STATIC_DRAW);
}

void Graphics::render() {
	glUseProgram(renderingProgram);
	glEnableVertexAttribArray(0);

	mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
	projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");

	glfwGetFramebufferSize(window, &width, &height);
	aspect = (float)width / (float)height;
	pMat = glm::perspective(1.57f, aspect, 0.1f, 1000.0f);

	vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
	mMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -2.0f, 0.0f));
	mvMat = vMat * mMat;
	
	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, model->getSize());
	glDisableVertexAttribArray(0);
	glUseProgram(0);
}

GLuint Graphics::loadShader(int shaderTYPE, const char* filePath) {
	ifstream fileStream(filePath, ios::in);
	string line = "";
	string shaderStr;
	GLint shaderCompiled;
	const char* shaderSrc;
	GLuint shaderRef;

	while (!fileStream.eof()) {
		getline(fileStream, line);
		shaderStr.append(line + "\n");
	}
	fileStream.close();

	
	shaderSrc = shaderStr.c_str();
	shaderRef = glCreateShader(shaderTYPE);
	glShaderSource(shaderRef, 1, &shaderSrc, NULL);
	glCompileShader(shaderRef);
	glGetShaderiv(shaderRef, GL_COMPILE_STATUS, &shaderCompiled);

	return shaderRef;
}

GLuint Graphics::createShaderProgram(const char* vp, const char* fp) {
	GLuint vShader = loadShader(GL_VERTEX_SHADER, vp);
	GLuint fShader = loadShader(GL_FRAGMENT_SHADER, fp);
	GLuint program = glCreateProgram();

	glAttachShader(program, vShader);
	glAttachShader(program, fShader);
	glLinkProgram(program);

	finalizeShaderProgram(program);

	return program;
}

int Graphics::finalizeShaderProgram(GLuint sprogram) {
	GLint linked;
	glLinkProgram(sprogram);
	checkOpenGLError();
	glGetProgramiv(sprogram, GL_LINK_STATUS, &linked);
	if (linked != 1)
	{
		cout << "linking failed" << endl;
		printProgramLog(sprogram);
	}
	return sprogram;
}

bool Graphics::checkOpenGLError() {
	bool foundError = false;
	int glErr = glGetError();
	while (glErr != GL_NO_ERROR) {
		cout << "glError: " << glErr << endl;
		foundError = true;
		glErr = glGetError();
	}
	return foundError;
}

void Graphics::printProgramLog(int prog) {
	int len = 0;
	int chWrittn = 0;
	char *log;
	glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
	if (len > 0) {
		log = (char *)malloc(len);
		glGetProgramInfoLog(prog, len, &chWrittn, log);
		cout << "Program Info Log: " << log << endl;
		free(log);
	}
}