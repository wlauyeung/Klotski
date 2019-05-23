#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <SOIL2/soil2.h>

class Texture {
private:
	GLuint textureID;
public:
	Texture(const char* filePath);
	~Texture(void);
	void mipmapping(void);
	GLuint getTextureID(void);
};

#endif // !TEXTURE_H
