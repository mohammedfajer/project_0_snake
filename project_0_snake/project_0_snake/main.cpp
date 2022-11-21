
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <string>

#include "Globals.h"
#include "Rectangle.h"
#include "Snake.h"
#include "Apple.h"
#include "SnakeBody.h"
#include "Grid.h"
#include "Line.h"
#include <stdlib.h>     /* srand, rand */

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


double xPos, yPos;

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	
	glfwGetCursorPos(window, &xPos, &xPos);

	std::cout << "Position: (" << xpos << ":" << ypos << ")";

	
	//exit(-1);
}


void isPointInsideAABB(int mouseX, int mouseY, Snake snake) {
	
	if (mouseX >= snake.position.x && mouseX <= snake.position.x + snake.width && mouseY >= snake.position.y && mouseY <= snake.position.y + snake.height) {
		std::cout << "Collided \n";
		exit(-1);
	}
	
}

void snakeEatsApple(Snake* s, Apple* a) {
	auto sP = s->position;
	auto aP = a->position;
	auto xCollision = sP.x + s->width > aP.x && sP.x < aP.x + a->width;
	auto yCollision = sP.y + s->height > aP.y && sP.y < aP.y + a->height;
	if (xCollision && yCollision) {
		a->shouldMove = true;
		s->eatApple();

	}
}

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
	//glfwSetCursorPosCallback(window, cursor_position_callback); 
	glfwSetCursorPosCallback(window, cursor_position_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	/*Rectangle redRect(100, 100, 50, 50, { 1.0f, 0.0f, 0.0f });
	Rectangle greenRect(300, 300, 100, 100, { 0.0f, 1.0f, 0.0f });*/


	Snake s({0, 0}, {50+16, 50+16}, DRAW_MODE_FILLED, { 0,1,0 });
	//s.body.setThickness(5);
	 
	Apple a({ 50+16,50+16 }, { 50+16,50+16 }, DRAW_MODE_OUTLINE);
	
	//SnakeBody sBody;

	/*
	Grid grid;
	grid.setThickness(5);

	grid.draw();

*/
	

	//Grid grid;
	//grid.setThickness(5);

	std::vector<Line> horizontalLines;
	for (int i = 0; i <= GRID_HEIGHT; i++) {
		auto startPoint = glm::vec2(0.0f, i * (16.0f + 50));
		auto endPoint = glm::vec2(SCR_WIDTH, i * (16.0f + 50));
		Line l(startPoint, endPoint, { 122 / 255.0f, 129 / 255.0f, 130 / 255.0f });
		horizontalLines.push_back(l);
	}

	std::vector<Line> verticalLines;
	for (int i = 0; i <= GRID_WIDTH; i++) {
		auto startPoint = glm::vec2(i * (16.0f + 50), 0.0f);
		auto endPoint = glm::vec2(i * (16.0f + 50), SCR_HEIGHT);
		Line l(startPoint, endPoint, { 122 / 255.0f, 129 / 255.0f, 130 / 255.0f });
		verticalLines.push_back(l);
	}

	Line line(glm::vec2(100, 100), glm::vec2(400, 400), { 1,1,1 });
	line.setThickness(2);
	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		do_joystick();
		glfwGetCursorPos(window, &xPos, &yPos);

		snakeEatsApple(&s, &a);

		glClearColor(34/255.0f, 32/255.0f, 38/255.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

	
		std::cout << "Apple Count : " << s.eatenApples() << std::endl;


		a.update(window);
		s.update(window);

		a.draw();
		s.draw();


		for (int i = 0; i < GRID_HEIGHT; i++) {
			
			horizontalLines[i].Draw();
		}

		for (int i = 0; i < GRID_WIDTH; i++) {

			verticalLines[i].Draw();
		}
		
		line.Draw();
		//std::cout << s.position.x << " " << s.position.y << std::endl;

		//isPointInsideAABB(xPos, yPos, s);

		




		
		
		//grid.draw();

		//sBody.update(window, &a);
		//sBody.draw();

		/*	a.update(window);
			a.draw();*/
		
		/*redRect.draw();
		greenRect.draw();*/

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}





