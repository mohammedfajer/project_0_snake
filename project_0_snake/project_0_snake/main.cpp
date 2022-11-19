
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <string>

#include "Globals.h"
#include "Rectangle.h"

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
void do_joystick() {
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
		}
		if (state.buttons[GLFW_GAMEPAD_BUTTON_Y]) {
		}
		if (state.buttons[GLFW_GAMEPAD_BUTTON_X]) {
		}
		if (state.buttons[GLFW_GAMEPAD_BUTTON_B]) {
		}
	}
}


int main() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	Rectangle redRect(100, 100, 50, 50, { 1.0f, 0.0f, 0.0f });
	Rectangle greenRect(300, 300, 100, 100, { 0.0f, 1.0f, 0.0f });
	
	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		do_joystick();

		glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		redRect.update(window);
		
		redRect.draw();
		greenRect.draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}





