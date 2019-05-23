#ifndef ENTITYRECTANGLE
#define ENTITYRECTANGLE

#include "entity.h"

class EntityRectangle : public Entity {
public:
	EntityRectangle(int x, int y, int width, int height, int isClickable, const char* filePath);

	void action(void);
};

#endif // !ENTITYCUBE