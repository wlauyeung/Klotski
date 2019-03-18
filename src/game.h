#ifndef GAME_H
#define GAME_H

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <vector>
#include "graphics.h"
#include "model.h"

class Game {

public:
	Game(const int width, const int height);
	~Game();

private:
	Graphics* graphics;
	Model* models;

	void init(GLFWwindow* window);
	void display(GLFWwindow* window, double currentTime);
};

#endif 
