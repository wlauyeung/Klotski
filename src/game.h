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

	void moveIsMade();
	void undo();

	static void registerModels();
private:
	Scene* currentScene;
	Scene* sceneTitle;
	Graphics* graphics;
	Stack* stack;

	void display(GLFWwindow* window);
};

#endif 
