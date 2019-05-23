#ifndef ENTITYEXITBUTTON_H
#define ENTITYEXITBUTTON_H

#include "entityUndoButton.h"
#include "../game.h"

class EntityExitButton : public EntityRectangle {
public:
	EntityExitButton(int x, int y, int width, int height, const char* filePath);

	void action(void);

private:
	int button;
};

#endif // !ENTITYCUBE