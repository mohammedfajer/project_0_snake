#include "Snake.h"
#include <iostream>


Snake::Snake(glm::vec2 position, glm::vec2 scale, int mode, Color c) : body(position.x, position.y, scale.x, scale.y, c, mode)
{
	this->position = position;
	width = scale.x;
	height = scale.y;
	appleAte = 0;
	speed = 0;
	
}

void Snake::update(GLFWwindow* window)
{
	buttons[0].currentState = glfwGetKey(window, GLFW_KEY_D);
	buttons[1].currentState = glfwGetKey(window, GLFW_KEY_A);
	buttons[2].currentState = glfwGetKey(window, GLFW_KEY_W);
	buttons[3].currentState = glfwGetKey(window, GLFW_KEY_S);

	if (buttons[0].currentState == GLFW_PRESS && buttons[0].previousState == GLFW_RELEASE) {
		std::cout << "Move To the Right \n";
		body.view = glm::translate(body.view, glm::vec3(speed + width, 0.0f, 0.0f));
		position.x += speed + width;
	}
	else if (buttons[1].currentState == GLFW_PRESS && buttons[1].previousState == GLFW_RELEASE) {
		std::cout << "Move To the Left \n";
		body.view = glm::translate(body.view, glm::vec3(-(speed + width), 0.0f, 0.0f));
		position.x -= (speed+width);

	}
	else if (buttons[2].currentState == GLFW_PRESS && buttons[2].previousState == GLFW_RELEASE) {
		std::cout << "Move Up\n";
		body.view = glm::translate(body.view, glm::vec3(0.0f, -(speed+height), 0.0f));
		position.y -= (speed+height);
		
	}
	else if (buttons[3].currentState == GLFW_PRESS && buttons[3].previousState == GLFW_RELEASE) {
		std::cout << "Move Down \n";
		body.view = glm::translate(body.view, glm::vec3(0.0f, (speed+height), 0.0f));
		position.y += speed+height;
	
	}
	
	buttons[0].previousState = buttons[0].currentState;
	buttons[1].previousState = buttons[1].currentState;
	buttons[2].previousState = buttons[2].currentState;
	buttons[3].previousState = buttons[3].currentState;

	int present = glfwJoystickPresent(GLFW_JOYSTICK_1);
	std::cout << "Joystick/Game pad 1 status: " << present << std::endl;
	if (present == 1) {
		int axes_count = 0;
		const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axes_count);
		std::cout << "Number of axes available : " << axes_count << std::endl;
	}
	GLFWgamepadstate state;
	if (glfwGetGamepadState(GLFW_JOYSTICK_1, &state)) {
		if (state.buttons[GLFW_GAMEPAD_BUTTON_A]) {
			std::cout << "Move Down \n";
			body.view = glm::translate(body.view, glm::vec3(0.0f, 5.0f, 0.0f));
			position.y += 5.0f;
		}
		else if (state.buttons[GLFW_GAMEPAD_BUTTON_Y]) {
			std::cout << "Move Up\n";
			body.view = glm::translate(body.view, glm::vec3(0.0f, -5.0f, 0.0f));
			position.y -= 5.0f;
		}
		else if (state.buttons[GLFW_GAMEPAD_BUTTON_X]) {
			std::cout << "Move To the Left \n";
			body.view = glm::translate(body.view, glm::vec3(-5.0f, 0.0f, 0.0f));
			position.x -= 5.0f;
		}
		else if (state.buttons[GLFW_GAMEPAD_BUTTON_B]) {
			std::cout << "Move To the Right \n";
			body.view = glm::translate(body.view, glm::vec3(5.0f, 0.0f, 0.0f));
			position.x += 5.0f;
		}
	}

	

}

void Snake::draw()
{
	body.draw();
	
}

