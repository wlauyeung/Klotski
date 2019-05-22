#include "Color.h"

const Color Color::RED = *(new Color(1.0f, 0.0f, 0.0f));
const Color Color::GREEN = *(new Color(0.0f, 1.0f, 0.0f));
const Color Color::BLUE = *(new Color(0.0f, 0.0f, 1.0f));
const Color Color::WHITE = *(new Color(1.0f, 1.0f, 1.0f));
const Color Color::BLACK = *(new Color(0.0f, 0.0f, 0.0f));
const Color Color::YELLOW = *(new Color(1.0f, 1.0f, 0.0f));

Color::Color(float r, float g, float b) {
	this->r = r;
	this->g = g;
	this->b = b;
}

Color::Color() {
	r = 1.0f;
	g = 1.0f;
	b = 1.0f;
}

Color::~Color() {

}

float Color::getR() {
	return r;
}

float Color::getG() {
	return g;
}

float Color::getB() {
	return b;
}

glm::vec3 Color::getRGB() {
	return glm::vec3(r, g, b);
}
