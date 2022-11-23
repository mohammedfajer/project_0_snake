#pragma once

#include "Rectangle.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "DoublyLinkedList.h"
#include "Rectangle.h"
#include "Apple.h"

class Snake
{
public:
	Snake() = default;
	Snake(GLFWwindow* window, Apple *apple);
public:
	void inputHandleKeyboard();
	void inputHandleJoystick();
public:
	void checkCollisionWithWalls();
	void checkCollisionWithApple();
	void checkCollisionWithBody();
public:
	void update();
	void draw();
private:
	void move();
	void moveBody();
	void grow();
public:
	int snakeDir;
	int speed;
private:
	DoublyLinkedList<Rectangle> body;
	unsigned int eatenAppleCount;
	bool isDead;
	bool key_moveRight;
	bool key_moveLeft;
	bool key_moveUp;
	bool key_moveDown;
	bool joy_moveRight;
	bool joy_moveLeft;
	bool joy_moveUp;
	bool joy_moveDown;
	GLFWwindow* window;
	Apple* apple;
	glm::vec2 headPosition;
	bool shouldGrow;
	

};