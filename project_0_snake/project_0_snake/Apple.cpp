#include "Apple.h"
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include "Globals.h"
Apple::Apple(glm::vec2 position, glm::vec2 scale, int mode) 
	: 
	body(position.x, position.y, scale.x, scale.y, { 1,0,0 }, mode)
{
	this->position = position;
	width = scale.x;
	height = scale.y;
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

glm::vec2 positions[] = {
	{100, 100}, {300, 300}, {400, 400}, {500, 500}
};

void Apple::moveToNewPosition(){ 
	/*auto posIdx = rand() % 4;
	auto pos = positions[posIdx];*/
	auto newX = (float) (rand() % 49 );
	auto newY = (float) (rand() % 41 );
	newX *= 16;
	newY *= 16;
	position = glm::vec2(newX, newY);
	body.update(newX, newY);
}
