#ifndef GAME_H
#define GAME_H

#include "graphics.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <vector>
#include "graphics.h"
#include "entities\entity.h"
#include "scenes\scene.h"
#include "scenes\sceneTitle.h"
#include "stack.h"

class Game {
public:
	Game(const int width, const int height);
	~Game(void);

	void setCurrentScene(Scene& s);
	Scene& getCurrentScene(void);
	void start(void);
	void stop(void);

	std::vector<std::vector<Entity*> >& getGameStack(void);
	void updateStack(void);
	void undo(void);

	void setTaggedEntity(Entity* e);
	Entity* getTaggedEntity(void);

	static void registerModels(void);
	static Game* game;
	static Game* getIntance();
	static void setInstance(Game* game);
	static int* startMousePos;
private:
	Scene* currentScene;
	Scene* sceneTitle;
	Stack* stack;
	GLFWwindow* window;
	Entity* taggedEntity;

	void display(GLFWwindow* window);
	static void onMouseClick(GLFWwindow* window, int button, int action, int mods);
};

#endif 
