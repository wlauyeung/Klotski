#include "game.h"

Game::Game(const int width, const int height) {

	if (!glfwInit()) { exit(EXIT_FAILURE); }
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	GLFWwindow* window = glfwCreateWindow(width, height, "Klotski", NULL, NULL);

	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
	glfwSwapInterval(1);

	graphics = new Graphics(window);
	
	registerModels();

	for (Model* m : Model::getModels()) {
		graphics->storeBufferData(m->getVertices(), m->getSize(), m->getVBOID());
	}
	
	sceneTitle = new SceneTitle();
	currentScene = sceneTitle;
	currentScene->load();

	stack = new Stack();
	
	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		display(window);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

Game::~Game() {
	delete sceneTitle;
	delete graphics;
	Model::deleteModels();
}

void Game::setCurrentScene(Scene& s) {
	currentScene = &s;
}

Scene& Game::getCurrentScene() {
	return *currentScene;
}

void Game::registerModels() {
	float* cubeVertices = new float[108]{
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, -1.0f, 1.0f,
		0.0f, -1.0f, 1.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		0.0f, -1.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		0.0f, -1.0f, 1.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
	};

	Model::CUBE = new Model(cubeVertices, 108, Graphics::genBuffer());
	
	float* rectangleVertices = new float[18]{
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f
	};

	Model::RECTANGLE = new Model(rectangleVertices, 18, Graphics::genBuffer());

	Model::getModels().push_back(Model::RECTANGLE);
	Model::getModels().push_back(Model::CUBE);
}

void Game::display(GLFWwindow* window) {
	for (Entity* e : currentScene->getEntities()) {
		graphics->render(*e);
	}
}

void Game::moveIsMade(){
	std::vector<Entity*> stackElem;

	for (Entity* e : currentScene->getEntities()) {
		stackElem.push_back(e);
	}
	stack->getStack().push_back(stackElem);
}

void Game::undo() {
	currentScene->setEntities(stack->getStack().back());
	stack->getStack().pop_back();
}

