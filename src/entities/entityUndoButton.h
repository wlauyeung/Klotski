#ifndef ENTITYUNDOBUTTON_H
#define ENTITYUNDOBUTTON_H

#include "entityRectangle.h"

class EntityUndoButton : public EntityRectangle {
public:
	EntityUndoButton(int x, int y, int width, int height, const char* filePath);
	
	void action(void);

private:
	int button;
};

#endif // !ENTITYCUBE