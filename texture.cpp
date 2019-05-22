#include "texture.h"

Texture::Texture(const char* filePath) {
	textureID = SOIL_load_OGL_texture(filePath,
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (textureID == 0) std::cout << "could not find texture file " << filePath << std::endl;
}
Texture::~Texture(void) {

}

void Texture::mipmapping() {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	if (glewIsSupported("GL_EXT_texture_filter_anisotropic")) {
		GLfloat anisoSetting = 0.0f;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &anisoSetting);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisoSetting);
	}
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

}
GLuint Texture::getTextureID(void) {
	return textureID;
}