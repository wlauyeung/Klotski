

#include "graphics.h"

vector<GLuint> Graphics::vaos;
vector<GLuint> Graphics::vbos;

Graphics::Graphics(GLFWwindow* window) {

	glfwGetFramebufferSize(window, &width, &height);
	aspect = (float)width / (float)height;
	glViewport(0, 0, width, height);
	pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);

	cameraX = 0.0f; cameraY = 0.0f; cameraZ = 8.0f;


	renderingProgram = createShaderProgram("shaders/vertShader.glsl", "shaders/fragShader.glsl");
}

Graphics::~Graphics() {
	for (GLuint i : vaos) {
		glDeleteVertexArrays(1, &i);
	}

	for (GLuint i : vbos) {
		glDeleteBuffers(1, &i);
	}
	
	glDeleteProgram(renderingProgram);
}

GLuint Graphics::genBuffer() {
	GLuint vboID, vaoID;
	glGenBuffers(1, &vboID);
	vbos.push_back(vboID);
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);
	vaos.push_back(vaoID);
	return vboID;
}

void Graphics::storeBufferData(GLfloat data[], int size, GLuint vboID) {
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(data), data, GL_STATIC_DRAW);
}

void Graphics::render(Entity& e) {
	glUseProgram(renderingProgram);
	glEnableVertexAttribArray(0);

	mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
	projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");

	vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX - 2.0f, -cameraY + 2.0f, -cameraZ - 2.0f));
	vMat = glm::rotate(vMat, 0.6f, glm::vec3(1.0f, 0.0f, 0.0f));

	sMat = glm::scale(glm::mat4(1.0f), glm::vec3(e.getScaleX(), e.getScaleY(), e.getScaleZ()));
	tMat = glm::translate(glm::mat4(1.0f), glm::vec3(e.getX(), e.getY(), e.getZ()));

	rMat = glm::rotate(glm::mat4(1.0f), e.getRotY(), glm::vec3(0.0f, 1.0f, 0.0f));
	rMat = glm::rotate(rMat, e.getRotX(), glm::vec3(1.0f, 0.0f, 0.0f));
	rMat = glm::rotate(rMat, e.getRotZ(), glm::vec3(0.0f, 0.0f, 1.0f));

	mMat = tMat * rMat * sMat;

	mvMat = vMat * mMat;

	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));
	glBindBuffer(GL_ARRAY_BUFFER, e.getModel().getVBOID());
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, e.getModel().getSize());
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