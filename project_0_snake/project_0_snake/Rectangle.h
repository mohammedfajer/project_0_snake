#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Color.h"
#include "Shader.h"
#include <vector>

#define DRAW_MODE_FILLED  0x12
#define DRAW_MODE_OUTLINE 0x13


class Rectangle {
public:
	Rectangle() = default;
	Rectangle(int x, int y, int width, int height, Color c, int mode);
	void draw();
	void setThickness(int thickenss);
	void update(int x, int y);
private:
	void set_vertices();
public:
	Shader shader;
	int width;
	int height;
	glm::vec2 position;
private:
	int x;
	int y;
	
	Color c;
	int mode;
private:
	GLuint VAO, VBO, EBO;
	
	float vertices[28];
	/*GLuint indices[6];*/
	
	std::vector<GLuint> indices;

public:

	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
};
