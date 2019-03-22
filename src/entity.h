#ifndef ENTITY_H
#define ENTITY_H

#include "model.h"

class Entity {
public:
	Entity(Model* model, float x, float y, float z, float rotX, float rotY, float rotZ);

	Entity(Model* model, float x, float y, float z);
	
	~Entity(void);

	float getX(void);
	float getY(void);
	float getZ(void);

	float getRotX(void);
	float getRotY(void);
	float getRotZ(void);

	Model& getModel(void);

	void setX(float x); 
	void setY(float y);
	void setZ(float z);

	void setRotX(float rotX);
	void setRotY(float rotY);
	void setRotZ(float rotZ);
private:
	Model* model;
	float x, y, z, rotX, rotY, rotZ;
};

#endif
