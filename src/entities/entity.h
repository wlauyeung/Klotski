#ifndef ENTITY_H
#define ENTITY_H

#include "../model.h"
#include "../color.h"

class Entity {
public:
	Entity(Model* model, float x, float y, float scaleX, float scaleY, const Color& color);
	
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

	Color getColor(void);
	void setColor(Color& color);

	void move(float x, float y);
private:
	Model* model;
	float x, y, scaleX, scaleY;
	Color color;
};

#endif
