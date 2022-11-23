
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <string>

#include "Globals.h"
#include "Rectangle.h"
#include "Snake.h"
#include "Apple.h"

#include "Line.h"
#include <stdlib.h>     /* srand, rand */


#include "Node.h"
#include "DoublyLinkedList.h"

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

double xPos, yPos;


int main() {
	/* initialize random seed: */
	srand(time(NULL));

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

	// Define Game Objects


	// Apple
	Apple apple ({ 200 , 100  }, { 50 ,50  }, DRAW_MODE_FILLED);

	// Snake
	Snake theSnake(window, &apple);
	
	
	// Setup Grid Lines
	std::vector<Line> horizontalLines;
	for (int i = 0; i <= GRID_HEIGHT; i++) {
		auto startPoint = glm::vec2(0.0f, i * 50);
		auto endPoint = glm::vec2(SCR_WIDTH, i * 50);
		Line l(startPoint, endPoint, { 122 / 255.0f, 129 / 255.0f, 130 / 255.0f });
		horizontalLines.push_back(l);
	}

	std::vector<Line> verticalLines;
	for (int i = 0; i <= GRID_WIDTH; i++) {
		auto startPoint = glm::vec2(i * 50, 0.0f);
		auto endPoint = glm::vec2(i * 50, SCR_HEIGHT);
		Line l(startPoint, endPoint, { 122 / 255.0f, 129 / 255.0f, 130 / 255.0f });
		verticalLines.push_back(l);
	}

	// Setup Time Variables
	double currentFrame = glfwGetTime();
	double lastFrame = currentFrame;
	double deltaTime;
	float nextMoveAt = 0;

	while (!glfwWindowShouldClose(window)) {
		
		// Compute Time
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Handle Window Input
		processInput(window);
		
		// Get Mouse Position
		glfwGetCursorPos(window, &xPos, &yPos);
		

		// Update Game Objects

		if (currentFrame > nextMoveAt) {
			nextMoveAt = glfwGetTime() + 0.15;
			apple.update(window);
			theSnake.update();
		}

		// Drawing

		glClearColor(34/255.0f, 32/255.0f, 38/255.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw Game Objects

		apple.draw();
		theSnake.draw();

		// Draw Grid Lines

		for (int i = 0; i < GRID_HEIGHT; i++) {
			horizontalLines[i].Draw();
		}

		for (int i = 0; i < GRID_WIDTH; i++) {
			verticalLines[i].Draw();
		}
		
		// Swap Frame buffers

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwTerminate();
	return 0;
}





