#include "game.h"

Game* Game::game;
int* Game::startMousePos;

Game::Game(const int width, const int height) {

	if (!glfwInit()) { exit(EXIT_FAILURE); }
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	window = glfwCreateWindow(width, height, "Klotski", NULL, NULL);

	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
	glfwSwapInterval(1);

	Graphics::init(window);
	
	glfwSetMouseButtonCallback(window, onMouseClick);

	glClearColor(0.849f, 0.849f, 0.849f, 0.849f);

	glEnable(GL_DEPTH_TEST);
}

Game::~Game() {
	delete sceneTitle;
	delete stack;
	delete startMousePos;
	glfwDestroyWindow(window);
	Model::deleteModels();
}

void Game::setCurrentScene(Scene& s) {
	currentScene = &s;
}

Scene& Game::getCurrentScene() {
	return *currentScene;
}

void Game::start() {
	registerModels();

	sceneTitle = new SceneTitle();
	currentScene = sceneTitle;
	currentScene->load();

	startMousePos = new int[2];

	stack = new Stack();

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

void Game::registerModels() {
	float* rectangleVertices = new float[18]{
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};
	float* rectangleTexCoords = new float[12]{
		0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f
	};

/*	float* rectangleColorCoords = new float[18] {
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
	};

	Model::RECTANGLE = new Model(rectangleVertices, 18,
		rectangleColorCoords, 18,
		Graphics::genVAO(rectangleVertices, 18, rectangleColorCoords, 18));
*/
	Model::RECTANGLE = new Model(rectangleVertices, 18,
		rectangleTexCoords, 12,
		Graphics::genVAO(rectangleVertices, 18, rectangleTexCoords, 12));

	Model::getModels().push_back(Model::RECTANGLE);
}

void Game::display(GLFWwindow* window) {
	for (Entity* e : currentScene->getEntities()) {
		Graphics::render(*e);
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

void Game::setTaggedEntity(Entity* e) {
	this->taggedEntity = e;
}

Entity * Game::getTaggedEntity() {
	return taggedEntity;
}

void Game::onMouseClick(GLFWwindow* window, int button, int action, int mods) {
	double x, y;

	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		glfwGetCursorPos(window, &x, &y);
		if (action == GLFW_PRESS) {
			std::vector<Entity*> entities = game->getCurrentScene().getEntities();
			for (int i = 0; i < entities.size(); i++) {
				EntityRectangle* e = static_cast<EntityRectangle*>(entities.at(i));
				if (x >= e->getX() && x <= e->getX() + e->getScaleX()
					&& y >= e->getY() && y <= e->getY() + e->getScaleY()) {
					if (e->isButton()) {
						e->action();
					}
					else {
						game->setTaggedEntity(e);
						startMousePos[0] = (int)x;
						startMousePos[1] = (int)y;
						i = entities.size();
					}
				}
			}
		}
		else {
			if (game->getTaggedEntity()) {
				if (x - startMousePos[0] != 0
					&& y - startMousePos[1] != 0) {
					if (abs(x - startMousePos[0]) > abs(y - startMousePos[1])) {
						if (x - startMousePos[0] < 0) {
							// move left
							game->getTaggedEntity()->move(-70, 0);
						}
						else {
							// move right
							game->getTaggedEntity()->move(70, 0);
						}
					}
					else {
						if (y - startMousePos[1] < 0) {
							// move dowm
							game->getTaggedEntity()->move(0, -70);
						}
						else {
							// move up
							game->getTaggedEntity()->move(0, 70);
						}
					}
				}
			}
			game->setTaggedEntity(0);
		}
	}

}

Game* Game::getIntance() {
	return game;
}

void Game::setInstance(Game* game) {
	Game::game = game;
}

