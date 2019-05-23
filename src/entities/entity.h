#ifndef ENTITY_H
#define ENTITY_H

#include "../model.h"
#include "../color.h"
#include "../texture.h"

class Entity {
public:
	Entity(Model* model, float x, float y, float scaleX, float scaleY, const char* filePath);
	
	~Entity(void);

	float getX(void);
	float getY(void);

	float getScaleX(void);
	float getScaleY(void);

	Model& getModel(void);

	void setX(float x); 
	void setY(float y);

	void setScaleX(float scaleX);
	void setScaleY(float scaleY);

	void move(float x, float y);
	GLuint getTextureID(void);
private:
	Model* model;
	float x, y, scaleX, scaleY;
	Texture* entityTex;
};

#endif
