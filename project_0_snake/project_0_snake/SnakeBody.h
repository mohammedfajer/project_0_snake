#pragma once

#include "Snake.h"
#include "Apple.h"

#include <vector>

#define SNAKE_DIR_UP 0
#define SNAKE_DIR_DOWN 1
#define SNAKE_DIR_LEFT 2
#define SNAKE_DIR_RIGHT 3

class SnakeBody
{
public:
	SnakeBody();
	void extendBody(int direction);
	bool collideWithWall();
	bool collideWithBody();
	bool collideWithApple(Apple* a);
	void update(GLFWwindow* window, Apple *a);
	void draw();
	~SnakeBody();
private:
	std::vector<Snake*> theSnake;
	int headIdx;
	int headDir;
	Apple* a;
	int tailIdx;
};

// Create snake body
// update(window, a);
// draw();