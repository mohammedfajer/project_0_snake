#pragma once

#include "Rectangle.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


struct ButtonState {
	int currentState;
	int previousState;
};

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
	
	float speed;

	ButtonState buttons[4];
};

