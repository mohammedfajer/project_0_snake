#include "Snake.h"
#include <iostream>

#include <chrono>
#include <thread>
Snake::Snake(glm::vec2 position, glm::vec2 scale, int mode, Color c) : body(position.x, position.y, scale.x, scale.y, c, mode)
{
	this->position = position;
	width = scale.x;
	height = scale.y;
	appleAte = 0;
	speed = 0;
	moveLeft = false;
	moveRight = false;
	moveUp = false;
	moveDown = false;
	j_moveLeft =  j_moveRight= j_moveUp= j_moveDown = false;
	
}

void Snake::update(GLFWwindow* window)
{
	
	
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		moveRight = true;
		moveLeft = false;
		moveUp = false;
		moveDown = false;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		moveRight = false;
		moveLeft = true;
		moveUp = false;
		moveDown = false;
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		moveRight = false;
		moveLeft = false;
		moveUp = true;
		moveDown = false;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		moveRight = false;
		moveLeft = false;
		moveUp = false;
		moveDown = true;
	}

	if (moveRight) {
		std::cout << "Move To the Right \n";
		
		body.view = glm::translate(body.view, glm::vec3((int)(speed + width) , 0.0f, 0.0f));
		position.x += (int)(speed + width);

	}
	 if (moveLeft) {
		std::cout << "Move To the Left \n";
		//std::this_thread::sleep_for(std::chrono::milliseconds(timeToWait));
		body.view = glm::translate(body.view, glm::vec3((int) - (speed + width) , 0.0f, 0.0f));
		position.x -= (int)(speed+width) ;

	}
	 if (moveUp) {
		std::cout << "Move Up\n";
		//std::this_thread::sleep_for(std::chrono::milliseconds(timeToWait));
		body.view = glm::translate(body.view, glm::vec3(0.0f, (int) - (speed + height), 0.0f));
		position.y -= (int)(speed+height);
		
	}
	  if (moveDown) {
		std::cout << "Move Down \n";
		// delay
		
		//std::this_thread::sleep_for(std::chrono::milliseconds(timeToWait));

		body.view = glm::translate(body.view, glm::vec3(0.0f, (int)(speed+height), 0.0f));
		position.y += (int)(speed+height);
	
	}
	
	  int present = glfwJoystickPresent(GLFW_JOYSTICK_1);
	  std::cout << "Joystick/Game pad 1 status: " << present << std::endl;
	  if (present == 1) {
		  int axes_count = 0;
		  const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axes_count);
		  std::cout << "Number of axes available : " << axes_count << std::endl;
	  }
	  GLFWgamepadstate state;
	  if (glfwGetGamepadState(GLFW_JOYSTICK_1, &state)) {

		  if (state.buttons[GLFW_GAMEPAD_BUTTON_B]) {
			  j_moveRight = true;
			  j_moveLeft = false;
			  j_moveUp = false;
			  j_moveDown = false;
		  }
		  if (state.buttons[GLFW_GAMEPAD_BUTTON_X]) {
			  j_moveRight = false;
			  j_moveLeft = true;
			  j_moveUp = false;
			  j_moveDown = false;
		  }
		  if (state.buttons[GLFW_GAMEPAD_BUTTON_Y]) {
			  j_moveRight = false;
			  j_moveLeft = false;
			  j_moveUp = true;
			  j_moveDown = false;
		  }
		  if (state.buttons[GLFW_GAMEPAD_BUTTON_A]) {
			  j_moveRight = false;
			  j_moveLeft = false;
			  j_moveUp = false;
			  j_moveDown = true;
		  }


		  if (j_moveDown) {
			  std::cout << "Move Down \n";
			  body.view = glm::translate(body.view, glm::vec3(0.0f, (int)(speed + height), 0.0f));
			  position.y += (int)(speed + height);
		  }
		  if (j_moveUp) {
			  std::cout << "Move Up\n";
			  //std::this_thread::sleep_for(std::chrono::milliseconds(timeToWait));
			  body.view = glm::translate(body.view, glm::vec3(0.0f, (int)-(speed + height), 0.0f));
			  position.y -= (int)(speed + height);
		  }
		  if (j_moveLeft) {
			  std::cout << "Move To the Left \n";
			  //std::this_thread::sleep_for(std::chrono::milliseconds(timeToWait));
			  body.view = glm::translate(body.view, glm::vec3((int)-(speed + width), 0.0f, 0.0f));
			  position.x -= (int)(speed + width);
		  }
		  if (j_moveRight) {
			  std::cout << "Move To the Right \n";

			  body.view = glm::translate(body.view, glm::vec3((int)(speed + width), 0.0f, 0.0f));
			  position.x += (int)(speed + width);
		  }
	  }

	
}

void Snake::draw()
{
	body.draw();
	
}

