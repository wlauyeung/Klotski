#ifndef ENTITYCUBE
#define ENTITYCUBE

#include "entity.h"

class EntityCube : public Entity {
public:
	EntityCube(int x, int y, int z, float rotX, float rotY, float rotZ,
		int width, int height, int depth);
	
	EntityCube(int x, int y, int width, int depth);
};

#endif // !ENTITYCUBE