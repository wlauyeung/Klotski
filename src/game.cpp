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
	Graphics::destroy();
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
	getGameStack().push_back(currentScene->getEntities());

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		display(window);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	this->~Game();
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void Game::stop() {
	glfwDestroyWindow(this->window);
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

std::vector<std::vector<Entity*> >& Game::getGameStack() {
	return stack->getStack();
}

void Game::updateStack() {
	std::vector<Entity*> stackElem;

	for (Entity* e : currentScene->getEntities()) {
		stackElem.push_back(e);
	}
	getGameStack().push_back(stackElem);
}

void Game::undo() {
	if (getGameStack().size() > 1) {
		currentScene->setEntities(getGameStack().back());
		getGameStack().pop_back();
	}
}

void Game::setTaggedEntity(Entity* e) {
	this->taggedEntity = e;
}

Entity* Game::getTaggedEntity() {
	return taggedEntity;
}

void Game::onMouseClick(GLFWwindow* window, int button, int action, int mods) {
	double x, y;

	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		glfwGetCursorPos(window, &x, &y);
		if (action == GLFW_PRESS) {
			std::vector<Entity*> entities = game->getCurrentScene().getEntities();
			for (int i = 0; i < entities.size(); i++) {
				Entity* e = entities.at(i);
				if (x >= e->getX() && x <= e->getX() + e->getScaleX()
					&& y >= e->getY() && y <= e->getY() + e->getScaleY()) {
					if (EntityUndoButton* button = dynamic_cast<EntityUndoButton*> (e)) {
						button->action(game->getGameStack());
						game->undo();
					}
					else if (EntityExitButton* button = dynamic_cast<EntityExitButton*> (e)) {
						button->action();
					}
					else if(e->isClickable()){
						game->setTaggedEntity(e);
						startMousePos[0] = (int)x;
						startMousePos[1] = (int)y;
						i = entities.size();
					}
				}
			}
		}
		else {
			int collision = 0;
			if (game->getTaggedEntity()) {
				if (x - startMousePos[0] != 0
					&& y - startMousePos[1] != 0) {
					game->updateStack();
					if (abs(x - startMousePos[0]) > abs(y - startMousePos[1])) {
						if (x - startMousePos[0] < 0) {
							// move left
							for (Entity* e : game->currentScene->getEntities()) {
								if (e->getFilePath() != "res/board.jpg") {
									if (
										(((e->getX() <= game->getTaggedEntity()->getX() - 70) &&
										((game->getTaggedEntity()->getX() - 70) < (e->getX() + e->getScaleX()))) &&

										(((e->getY() <= game->getTaggedEntity()->getY()) &&
										(game->getTaggedEntity()->getY() < (e->getY() + e->getScaleY()))) ||
										(e->getY() < (game->getTaggedEntity()->getY() + game->getTaggedEntity()->getScaleY()) &&
										(game->getTaggedEntity()->getY() + game->getTaggedEntity()->getScaleY() <= (e->getY() + e->getScaleY()))))) ||
										(game->getTaggedEntity()->getX() - 70 < 500)
										)
									{
										collision = 1;
									}
								}
							}
							if (!collision) {
								game->getTaggedEntity()->move(-70, 0);
							}
							collision = 0;
						}
						else {
							// move right
							for (Entity* e : game->currentScene->getEntities()) {
								if (e->getFilePath() != "res/board.jpg") {
									if (
										(((e->getX() < game->getTaggedEntity()->getX() + game->getTaggedEntity()->getScaleX() + 70) &&
										((game->getTaggedEntity()->getX() + game->getTaggedEntity()->getScaleX() + 70) <= (e->getX() + e->getScaleX()))) &&

										(((e->getY() <= game->getTaggedEntity()->getY()) &&
										(game->getTaggedEntity()->getY() < (e->getY() + e->getScaleY()))) ||
										(e->getY() < (game->getTaggedEntity()->getY() + game->getTaggedEntity()->getScaleY()) &&
										(game->getTaggedEntity()->getY() + game->getTaggedEntity()->getScaleY() <= (e->getY() + e->getScaleY()))))) ||
										(game->getTaggedEntity()->getX() + game->getTaggedEntity()->getScaleX() + 70 > 780)
										)
									{
										collision = 1;
									}
								}
							}
							if (!collision) {
								game->getTaggedEntity()->move(70, 0);
							}
							collision = 0;
						}
					}
					else {
						if (y - startMousePos[1] < 0) {
							// move up
							for (Entity* e : game->currentScene->getEntities()) {
								if (e->getFilePath() != "res/board.jpg") {
									if (
										(((e->getY() <= game->getTaggedEntity()->getY() - 70) &&
										((game->getTaggedEntity()->getY() - 70) < e->getY() + e->getScaleY())) &&

										(((e->getX() <= game->getTaggedEntity()->getX()) &&
										(game->getTaggedEntity()->getX() < (e->getX() + e->getScaleX()))) ||
										(e->getX() < (game->getTaggedEntity()->getX() + game->getTaggedEntity()->getScaleX()) &&
										(game->getTaggedEntity()->getX() + game->getTaggedEntity()->getScaleX() <= (e->getX() + e->getScaleX()))))) ||
										(game->getTaggedEntity()->getY() - 70 < 160)
										)
									{
										collision = 1;
									}
								}
							}
							if (!collision) {
								game->getTaggedEntity()->move(0, -70);
							}
							collision = 0;
						}
						else {
							// move down
							for (Entity* e : game->currentScene->getEntities()) {
								if (e->getFilePath() != "res/board.jpg") {
									if (
										(((e->getY() < game->getTaggedEntity()->getY() + game->getTaggedEntity()->getScaleY() + 70) &&
										((game->getTaggedEntity()->getY() + game->getTaggedEntity()->getScaleY() + 70) <= (e->getY() + e->getScaleY()))) &&

										(((e->getX() <= game->getTaggedEntity()->getX()) &&
										(game->getTaggedEntity()->getX() < (e->getX() + e->getScaleX()))) ||
										(e->getX() < (game->getTaggedEntity()->getX() + game->getTaggedEntity()->getScaleX()) &&
										(game->getTaggedEntity()->getX() + game->getTaggedEntity()->getScaleX() <= (e->getX() + e->getScaleX()))))) ||
										(game->getTaggedEntity()->getY() + game->getTaggedEntity()->getScaleX() + 70 > 510)
										)
									{
										collision = 1;
									}
								}
							}
							if (!collision) {
								game->getTaggedEntity()->move(0, 70);
							}
							collision = 0;
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

