#pragma once

#include "Rectangle.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



class Snake {
public:
	Snake(glm::vec2 position, glm::vec2 scale, int mode, Color c);
	void update(GLFWwindow* window);
	void draw();
	void eatApple() { appleAte++;  }
	int eatenApples() { return appleAte; }
	
public:
	glm::vec2 position;
	int width;
	int height;
	Rectangle body;
private:

	glm::vec2 rotation;
	glm::vec2 scale;
	int appleAte;
	int timeToWait;
	float speed;

	bool moveLeft, moveRight, moveUp, moveDown;
	bool j_moveLeft, j_moveRight, j_moveUp, j_moveDown;
};

