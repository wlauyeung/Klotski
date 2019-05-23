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
	delete entityStack;
	delete coorStack;
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

	entityStack = new Stack<Entity*>();
	coorStack = new Stack<int>();

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

std::vector<Entity*>* Game::getEntityStack() {
	return entityStack->getStack();
}

std::vector<int>* Game::getIntStack() {
	return coorStack->getStack();
}

void Game::updateStacks(Entity* e, int x, int y) {
	getEntityStack()->push_back(e);
	getIntStack()->push_back((int)(e->getY()) - y);
	getIntStack()->push_back((int)(e->getX()) - x);
}

Entity* Game::entityUndo() {
	Entity* entity = 0;
	if (getEntityStack()->size() > 0) {
		entity = getEntityStack()->back();
		//printf("%d, %d", (int)entity->getX(), (int)entity->getY()); coordinates are right
		getEntityStack()->pop_back();
	}
	//printf("%d, %d", (int)entity->getX(), (int)entity->getY()); coordinates are right
	return entity;
}

int* Game::coorUndo() {
	int xCoor, yCoor;
	int* coordinates = new int[2];
	if (getIntStack()->size() > 1) {
		xCoor = (int)getIntStack()->back();
		getIntStack()->pop_back();
		yCoor = (int)getIntStack()->back();
		getIntStack()->pop_back();
		*(coordinates + 0) = xCoor;
		*(coordinates + 1) = yCoor;
	}
	return coordinates;
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
						Entity* entityToMove = 0;
						int* currentCoor = new int[2];
						int* previousCoor;
						button->action();
						entityToMove = game->entityUndo();
						if (&(*entityToMove)) {
							printf("Undo!\n");
							previousCoor = game->coorUndo();
							*(currentCoor + 0) = (int)(entityToMove->getX()); 
							*(currentCoor + 1)= ((int)(entityToMove->getY()));

							entityToMove->move(previousCoor[0] - currentCoor[0], previousCoor[1] - currentCoor[1]);
						}
						else {
							printf("Nothing to undo!\n");
						}
					}
					else if (EntityExitButton* button = dynamic_cast<EntityExitButton*> (e)) {
						button->action();
					}
					else if (e->isClickable()) {
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
										(game->getTaggedEntity()->getX() - 70 < 90)
										)
									{
										collision = 1;
									}
								}
							}
							if (!collision) {
								game->getTaggedEntity()->move(-70, 0);
								game->updateStacks(game->getTaggedEntity(), -70, 0);
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
										(game->getTaggedEntity()->getX() + game->getTaggedEntity()->getScaleX() + 70 > 370)
										)
									{
										collision = 1;
									}
								}
							}
							if (!collision) {
								game->getTaggedEntity()->move(70, 0); 
								game->updateStacks(game->getTaggedEntity(), 70, 0);
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
										(game->getTaggedEntity()->getY() - 70 < 190)
										)
									{
										collision = 1;
									}
								}
							}
							if (!collision) {
								game->getTaggedEntity()->move(0, -70);
								game->updateStacks(game->getTaggedEntity(), 0, -70);
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
										(game->getTaggedEntity()->getY() + game->getTaggedEntity()->getScaleX() + 70 > 540)
										)
									{
										collision = 1;
									}
								}
							}
							if (!collision) {
								game->getTaggedEntity()->move(0, 70);
								game->updateStacks(game->getTaggedEntity(), 0, 70);
							}
							game->updateStacks(game->getTaggedEntity(), 0, 70);
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

