#include "Apple.h"
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include "Globals.h"


float clip(float n, float lower, float upper) {
	return std::max(lower, std::min(n, upper));
}

Apple::Apple(glm::vec2 position, glm::vec2 scale, int mode) 
	: 
	body(position.x, position.y, scale.x, scale.y, { 1,0,0 }, mode)
{
	this->position = position;
	width = scale.x;
	height = scale.y;
	active = true;

	for (int row = 0; row < GRID_HEIGHT; row++) {
		for (int col = 0; col < GRID_WIDTH; col++) {
			float x = row * 50;
			float y = col * 50;
			x = clip(x, 0, SCR_WIDTH - 50);
			y = clip(y, 0, SCR_HEIGHT - 50);
			
			applePositions[row][col] = {x ,y};
		}
	}
}

void Apple::update(GLFWwindow* window)
{
	if (shouldMove) {
		moveToNewPosition();
		shouldMove = false;
	}
}

void Apple::draw()
{
	body.draw();
}





void Apple::moveToNewPosition(){ 
	int xId = rand() % GRID_WIDTH - 1;
	int yId = rand() % GRID_HEIGHT - 1;
	auto pos = applePositions[yId][xId];
	position = glm::vec2(pos.x, pos.y);
	body.update(position.x, position.y);
}
