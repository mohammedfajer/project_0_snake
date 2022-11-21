#include "SnakeBody.h"
#include "Globals.h"
#include <iostream>

SnakeBody::SnakeBody()
{
	Snake* s = new Snake({ 500, 100 }, { 50, 50 }, DRAW_MODE_FILLED, { 0,1,0 });
	s->body.setThickness(5);
	
	theSnake.push_back(s);
	headIdx = 0;
	tailIdx = 0;
}

void SnakeBody::extendBody(int direction)
{

	std::cout << "EXTEND = DIR = " << direction << std::endl;

	//while (1) {}

	switch (direction) {

	case SNAKE_DIR_UP:
	{
		
		auto tailBody = theSnake[tailIdx];
		auto newX = tailBody->position.x;
		auto newY = tailBody->position.y + tailBody->height;
		Snake *s = new Snake({ newX, newY }, { 50, 50 }, DRAW_MODE_FILLED, {0,1,0});
		s->body.setThickness(5);
		theSnake.emplace_back(s);
		tailIdx++;
		break;
	}
		
	case SNAKE_DIR_DOWN:
	{
		auto tailBody = theSnake[tailIdx];
		auto newX = tailBody->position.x;
		auto newY = tailBody->position.y - tailBody->height;
		Snake* s = new Snake({ newX, newY }, { 50, 50 }, DRAW_MODE_FILLED, { 0,1,0 });
		s->body.setThickness(5);
		theSnake.emplace_back(s);
		tailIdx++;
		break;
	}
		break;
	case SNAKE_DIR_LEFT:
	{
		auto tailBody = theSnake[tailIdx];
		auto newX = tailBody->position.x + tailBody->width;
		auto newY = tailBody->position.y;
		Snake* s = new Snake({ newX, newY }, { 50, 50 }, DRAW_MODE_FILLED, { 0,1,0 });
		s->body.setThickness(5);
		theSnake.emplace_back(s);
		tailIdx++;
		break;
	}
		break;
	case SNAKE_DIR_RIGHT:
	{
		auto tailBody = theSnake[tailIdx];
		auto newX = tailBody->position.x - tailBody->width;
		auto newY = tailBody->position.y;
		Snake* s = new Snake({ newX, newY }, { 50, 50 }, DRAW_MODE_FILLED, { 0,1,0 });
		s->body.setThickness(5);
		theSnake.emplace_back(s);
		tailIdx++;
		break;
	}
		break;
	}
}

bool SnakeBody::collideWithWall()
{
	auto headBody = theSnake[headIdx];

	if (headBody->position.x < 0 || headBody->position.x + headBody->width > SCR_WIDTH) {
		return true;
	}

	if (headBody->position.y < 0 || headBody->position.y + headBody->height > SCR_HEIGHT) {
		return true;
	}

	return false;
}

bool SnakeBody::collideWithBody()
{

	/*auto sP = s->position;
	auto aP = a->position;
	auto xCollision = sP.x + s->width > aP.x && sP.x < aP.x + a->width;
	auto yCollision = sP.y + s->height > aP.y && sP.y < aP.y + a->height;
	if (xCollision && yCollision) {
		a->shouldMove = true;
		s->eatApple();
	}*/

	auto headBody = theSnake[headIdx];

	for (int i = 1; i < theSnake.size(); i++) {
		auto body = theSnake[i];

		auto xCollision = headBody->position.x + headBody->width > body->position.x 
			&& headBody->position.x < body->position.x + body->height;
		auto yCollision = headBody->position.y + headBody->height > body->position.y 
			&& headBody->position.y < body->position.y + body->height;
		
		if (xCollision && yCollision) {
			return true;
		}
	
	}

	return false;
}

bool SnakeBody::collideWithApple(Apple* a)
{
	auto headBody = theSnake[headIdx];
	auto sP = headBody->position;
	auto aP = a->position;
	auto xCollision = sP.x + headBody->width > aP.x && sP.x < aP.x + a->width;
	auto yCollision = sP.y + headBody->height > aP.y && sP.y < aP.y + a->height;
	if (xCollision && yCollision) {
		
		return true;
	}

	return false;
}

void SnakeBody::update(GLFWwindow* window, Apple* a){

	this->a = a;
	//auto& h = theSnake[headIdx];
	for (auto& b : theSnake) {
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			std::cout << "Move To the Right \n";
			b->body.view = glm::translate(b->body.view, glm::vec3(5.0f, 0.0f, 0.0f));
			b->position.x += 5.0f;
			headDir = SNAKE_DIR_RIGHT;
		}
		else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			std::cout << "Move To the Left \n";
			b->body.view = glm::translate(b->body.view, glm::vec3(-5.0f, 0.0f, 0.0f));
			b->position.x -= 5.0f;
			headDir = SNAKE_DIR_LEFT;
		}
		else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			std::cout << "Move Up\n";
			b->body.view = glm::translate(b->body.view, glm::vec3(0.0f, -5.0f, 0.0f));
			b->position.y -= 5.0f;
			headDir = SNAKE_DIR_UP;
		}
		else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			std::cout << "Move Down \n";
			b->body.view = glm::translate(b->body.view, glm::vec3(0.0f, 5.0f, 0.0f));
			b->position.y += 5.0f;
			b->position.y += 5.0f;
			headDir = SNAKE_DIR_DOWN;
		}
	}

	if (collideWithWall()) {
		std::cout << "Collided with wall\n";
		exit(-1);
	}
	if (collideWithBody()) {
		std::cout << "Collided with body\n";
		exit(-1);
	}
	if (collideWithApple(a)) {
		std::cout << "Collided with Apple\n";
		theSnake[headIdx]->eatApple();
		a->shouldMove = true;
		//a->update(window);
		extendBody(headDir);
		//exit(-1);DDDDD
	}
	
}

void SnakeBody::draw()
{
	for (auto& b : theSnake) {
		b->draw();
	}

	a->draw();
}

SnakeBody::~SnakeBody()
{
	for (auto c : theSnake) {
		delete c;
	}
}
