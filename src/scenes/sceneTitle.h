#ifndef SCENETITLE_H
#define SCENETITLE_H

#include "scene.h"

class SceneTitle : public Scene {
public:
	SceneTitle(void);
	~SceneTitle(void);
	void load();
	void unload();
};
#endif 
