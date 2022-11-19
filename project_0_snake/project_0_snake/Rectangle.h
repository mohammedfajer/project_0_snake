#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Color.h"
#include "Shader.h"




class Rectangle {
public:
	Rectangle(int x, int y, int width, int height, Color c);
	void draw();
	void update(GLFWwindow* window);
private:
	void set_vertices();
public:
	Shader shader;
private:
	int x;
	int y;
	int width;
	int height;
	Color c;
private:
	GLuint VAO, VBO, EBO;
	
	float vertices[28];
	GLuint indices[6];

	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
};
