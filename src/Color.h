#ifndef COLOR_H
#define COLOR_H

#include <glm\glm.hpp>

class Color {
public:
	static const Color RED;
	static const Color GREEN;
	static const Color BLUE;
	static const Color WHITE;
	static const Color BLACK;
	static const Color YELLOW;

	Color(float r, float g, float b);
	Color();
	~Color(void);

	float getR(void);
	float getG(void);
	float getB(void);
	glm::vec3 getRGB(void);
private:
	float r, g, b;
};

#endif // !COLOR_H
