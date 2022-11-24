#include "Snake.h"
#include <iostream>
#include "Globals.h"


Snake::Snake(GLFWwindow* window, Apple* apple) : window(window), isDead(false) , apple(apple)
{
	Rectangle snakeHead(50, 50, 50, 50, { 0.1,0.8,0.1 }, DRAW_MODE_FILLED);
	Rectangle snakeBody(100, 50, 50, 50, { 0, 1, 0 }, DRAW_MODE_FILLED);
	Rectangle snakeTail(150, 50, 50, 50, { 0, 1, 0 }, DRAW_MODE_FILLED);

	body.addFront(snakeHead);
	body.addEnd(snakeBody);
	body.addEnd(snakeTail);

	speed = 50;
	shouldGrow = false;
}

void Snake::inputHandleKeyboard() {
	snakeDir = (int)SNAKE_DIRECTION::STILL;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {

		joy_moveLeft = joy_moveRight = joy_moveUp = joy_moveDown = false;
		key_moveRight = true;
		key_moveLeft = false;
		key_moveUp = false;
		key_moveDown = false;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		joy_moveLeft = joy_moveRight = joy_moveUp = joy_moveDown = false;
		key_moveRight = false;
		key_moveLeft = true;
		key_moveUp = false;
		key_moveDown = false;
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		joy_moveLeft = joy_moveRight = joy_moveUp = joy_moveDown = false;
		key_moveRight = false;
		key_moveLeft = false;
		key_moveUp = true;
		key_moveDown = false;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		joy_moveLeft = joy_moveRight = joy_moveUp = joy_moveDown = false;
		key_moveRight = false;
		key_moveLeft = false;
		key_moveUp = false;
		key_moveDown = true;
	}
	if (key_moveRight) {
		std::cout << "Move To the Right \n";
		snakeDir = (int)SNAKE_DIRECTION::RIGHT;
	}
	if (key_moveLeft) {
		std::cout << "Move To the Left \n";
		snakeDir = (int)SNAKE_DIRECTION::LEFT;
	}
	if (key_moveUp) {
		std::cout << "Move Up\n";
		snakeDir = (int)SNAKE_DIRECTION::UP;	
	}
	if (key_moveDown) {
		std::cout << "Move Down \n";
		snakeDir = (int)SNAKE_DIRECTION::DOWN;
	}
}

void Snake::inputHandleJoystick() {
	snakeDir = (int)SNAKE_DIRECTION::STILL;
	int present = glfwJoystickPresent(GLFW_JOYSTICK_1);
	if (present == 1) {
		int axes_count = 0;
		const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axes_count);
	}
	GLFWgamepadstate state;
	if (glfwGetGamepadState(GLFW_JOYSTICK_1, &state)) {
		if (state.buttons[GLFW_GAMEPAD_BUTTON_B]) {
			key_moveLeft = key_moveRight = key_moveUp = key_moveDown = false;
			joy_moveRight = true;
			joy_moveLeft = false;
			joy_moveUp = false;
			joy_moveDown = false;
		}
		if (state.buttons[GLFW_GAMEPAD_BUTTON_X]) {
			key_moveLeft = key_moveRight = key_moveUp = key_moveDown = false;
			joy_moveRight = false;
			joy_moveLeft = true;
			joy_moveUp = false;
			joy_moveDown = false;
		}
		if (state.buttons[GLFW_GAMEPAD_BUTTON_Y]) {
			key_moveLeft = key_moveRight = key_moveUp = key_moveDown = false;
			joy_moveRight = false;
			joy_moveLeft = false;
			joy_moveUp = true;
			joy_moveDown = false;
		}
		if (state.buttons[GLFW_GAMEPAD_BUTTON_A]) {
			key_moveLeft = key_moveRight = key_moveUp = key_moveDown = false;
			joy_moveRight = false;
			joy_moveLeft = false;
			joy_moveUp = false;
			joy_moveDown = true;
		}
		if (joy_moveDown) {
			std::cout << "Move Down \n";
			snakeDir = (int)SNAKE_DIRECTION::DOWN;
		}
		if (joy_moveUp) {
			std::cout << "Move Up\n";
			snakeDir = (int)SNAKE_DIRECTION::UP;
		}
		if (joy_moveLeft) {
			std::cout << "Move To the Left \n";
			snakeDir = (int)SNAKE_DIRECTION::LEFT;
		}
		if (joy_moveRight) {
			std::cout << "Move To the Right \n";
			snakeDir = (int)SNAKE_DIRECTION::RIGHT;
		}
	}
}

void Snake::checkCollisionWithWalls(){
	// if head hits wall
	// if body hits wall

	auto snakeHeadPos = body.head->data.position;

	if (snakeHeadPos.x + body.head->data.width > SCR_WIDTH || snakeHeadPos.x < 0) {

		std::cout << "Collision with wall ! \n";
		isDead = true;
	}

	if (snakeHeadPos.y + body.head->data.height > SCR_HEIGHT || snakeHeadPos.y < 0) {

		std::cout << "Collision with wall ! \n";
		isDead = true;
	}

}

void Snake::checkCollisionWithApple(){

	auto head = body.head;

	auto applePosition = apple->position;

	auto xCollision = head->data.position.x + head->data.width > applePosition.x && head->data.position.x < applePosition.x + apple->width;
	auto yCollision = head->data.position.y + head->data.height > applePosition.y && head->data.position.y < applePosition.y + apple->height;

	if (xCollision && yCollision) {
		apple->shouldMove = true;
		eatenAppleCount++;

		// 
		shouldGrow = true;
	}
	else {
		shouldGrow = false;
	}

}

void Snake::checkCollisionWithBody(){
	// if head or body hit head or body
}

void Snake::update() {
	if (!isDead) {
		// Handle Input
		inputHandleKeyboard();
		inputHandleJoystick();

		// Snake Movement
		move();
		
		// Handle Collision
		checkCollisionWithWalls();
		checkCollisionWithBody();
		checkCollisionWithApple();

		// Snake Grow 
		grow();

	}
}

void Snake::draw() {
	if (!isDead) {
		auto current = body.head;
		while (current != nullptr) {
			current->data.draw();
			current = current->next;
		}
	}
}

void Snake::move() {

	// Every block takes in the position of its previous block
	if (key_moveRight || joy_moveRight) {
		moveBody();
		body.head->data.view = glm::translate(body.head->data.view, glm::vec3(speed, 0.0f, 0.0f));
		body.head->data.position.x += speed;
		
	}
	if (key_moveLeft || joy_moveLeft) {
		moveBody();
		body.head->data.view = glm::translate(body.head->data.view, glm::vec3(-speed, 0.0f, 0.0f));
		body.head->data.position.x -= speed;
		
	}
	if (key_moveUp || joy_moveUp) {
		moveBody();
		body.head->data.view = glm::translate(body.head->data.view, glm::vec3(0.0f, -speed, 0.0f));
		body.head->data.position.y -= speed;
		
	}
	if (key_moveDown || joy_moveDown) {
		moveBody();
		body.head->data.view = glm::translate(body.head->data.view, glm::vec3(0.0f, speed, 0.0f));
		body.head->data.position.y += speed;
		
	}
}

void Snake::moveBody() {
	auto current = body.tail;
	while (current != body.head) {

		//current->data.view = glm::translate(current->prev->data.view, glm::vec3(current->data.position.x, current->data.position.y, 0.0f));

		auto prevPos = current->prev->data.position;
		current->data.position = prevPos;
		current->data.update(prevPos.x, prevPos.y);
		//headPosition += current->data.position;


		current = current->prev;
	}
	//auto prevPos = body.head->data.position;
	//current->data.position = prevPos;
	//current->data.update(prevPos.x, prevPos.y);

}

void Snake::grow() {
	if (shouldGrow) {
		std::cout << "Growing ....\n";
		std::cout << "Apples Eaten So Far := " << eatenAppleCount << std::endl;
		std::cout << "Snake Direction := " << snakeDir << std::endl;
		Rectangle bodyPart(body.tail->data.position.x, body.tail->data.position.y, 50, 50, { 0,1,0 }, DRAW_MODE_FILLED);
		body.addEnd(bodyPart);
		shouldGrow = false;
	}
}