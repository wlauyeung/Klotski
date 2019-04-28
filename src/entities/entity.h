#ifndef ENTITY_H
#define ENTITY_H

#include "../model.h"

class Entity {
public:
	Entity(Model* model, float x, float y, float z, float rotX, float rotY, float rotZ,
		float scaleX, float scaleY, float scaleZ);
	Entity(Model* model, float x, float y, float z, float rotX, float rotY, float rotZ);
	Entity(Model* model, float x, float y, float z);
	
	~Entity(void);

	float getX(void);
	float getY(void);
	float getZ(void);

	float getRotX(void);
	float getRotY(void);
	float getRotZ(void);

	float getScaleX(void);
	float getScaleY(void);
	float getScaleZ(void);

	Model& getModel(void);

	void setX(float x); 
	void setY(float y);
	void setZ(float z);

	void setRotX(float rotX);
	void setRotY(float rotY);
	void setRotZ(float rotZ);

	void setScaleX(float scaleX);
	void setScaleY(float scaleY);
	void setScaleZ(float scaleZ);
private:
	Model* model;
	float x, y, z, rotX, rotY, rotZ, scaleX, scaleY, scaleZ;
};

#endif
