#pragma once

#include "Rectangle.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Globals.h"


class Apple {
public:
	Apple(glm::vec2 position, glm::vec2 scale, int mode);
	void update(GLFWwindow* window);
	void draw();
	void moveToNewPosition();
	bool shouldMove = false;
public:
	glm::vec2 position;
	int width;
	int height;
	Rectangle body;
	bool active;
private:
	glm::vec2 rotation;
	glm::vec2 scale;
	glm::vec2 applePositions[GRID_HEIGHT][GRID_WIDTH];
	
};

