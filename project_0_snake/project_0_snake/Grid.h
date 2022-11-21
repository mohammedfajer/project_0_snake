#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Color.h"
#include "Shader.h"
#include <vector>

class Grid
{
public:
	Grid();
	void setThickness(int thickness);
	void setColor(Color c);
	void draw();
private:
	void set_vertices();

public:

	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
private:
	GLuint VAO, VBO, EBO;
	std::vector<glm::vec3> vertices;
	std::vector<glm::uvec3> indices;
	Color color;
	int thickness;
	Shader shader;
};

/*
	Grid grid;
	grid.setThickness(5);

	grid.draw();
	
*/
