#include "graphics.h"

vector<GLuint> Graphics::vaos;
vector<GLuint> Graphics::vbos;
vector<int> Graphics::attribs;
int Graphics::width, Graphics::height;
GLuint Graphics::renderingProgram;
GLuint Graphics::mLoc, Graphics::projLoc;
glm::mat4 Graphics::pMat, Graphics::mMat, Graphics::tMat, Graphics::sMat;

void Graphics::init(GLFWwindow* window) {
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	pMat = glm::ortho(0.0f, (float)width, (float)height, 0.0f);

	renderingProgram = createShaderProgram("shaders/vertShader.glsl", "shaders/fragShader.glsl");
}

void Graphics::destroy() {
	for (GLuint i : vaos) {
		glDeleteVertexArrays(1, &i);
	}

	for (GLuint i : vbos) {
		glDeleteBuffers(1, &i);
	}

	glDeleteProgram(renderingProgram);
}

void Graphics::render(Entity& e) {
	glUseProgram(renderingProgram);
	glBindVertexArray(e.getModel().getVaoID());
	enableVertexAttribArrays();

	mLoc = glGetUniformLocation(renderingProgram, "m_matrix");
	projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");

	sMat = glm::scale(glm::mat4(1.0f), glm::vec3(e.getScaleX(), e.getScaleY(), 1.0f));
	tMat = glm::translate(glm::mat4(1.0f), glm::vec3(e.getX(), e.getY(), 1.0f));
	mMat = tMat * sMat;

	glUniformMatrix4fv(mLoc, 1, GL_FALSE, glm::value_ptr(mMat));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

	glBindTexture(GL_TEXTURE_2D, e.getTextureID());
	glDrawArrays(GL_TRIANGLES, 0, e.getModel().getVerticesSize());

	disableVertexAttribArrays();
	glUseProgram(0);
}

GLuint Graphics::storeBufferData(int attribNumber, GLfloat data[], int size, int dim) {
	GLuint vboID;
	attribs.push_back(attribNumber);
	glGenBuffers(1, &vboID);
	vbos.push_back(vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(data), data, GL_STATIC_DRAW);
	glVertexAttribPointer(attribNumber, dim, GL_FLOAT, false, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return vboID;
}

GLuint Graphics::genVAO(float* vertices, int size, float* texCoords, int texCoordsSize) {
	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	vaos.push_back(vaoID);
	glBindVertexArray(vaoID);
	storeBufferData(0, vertices, size, 3);
	storeBufferData(1, texCoords, texCoordsSize, 2);

	return vaoID;
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

void Graphics::enableVertexAttribArrays() {
	for (int i : attribs) {
		glEnableVertexAttribArray(i);
	}
}

void Graphics::disableVertexAttribArrays() {
	for (int i : attribs) {
		glDisableVertexAttribArray(i);
	}
}

