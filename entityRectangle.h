#ifndef ENTITYRECTANGLE
#define ENTITYRECTANGLE

#include "entity.h"

class EntityRectangle : public Entity {
public:
	EntityRectangle(int x, int y, int width, int height, const Color& color, int isButton, const char* filePath);

	int isButton(void);
	void action(void);

private:
	int button;
};

#endif // !ENTITYCUBE