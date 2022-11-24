#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "Color.h"
#include "Shader.h"
#include <vector>

class Sprite 
{
public:
	Shader shader;
	int width, height, nrChannels;
	glm::vec2 position;
	glm::mat4 model, view, projection;
private:
	GLuint VAO, VBO, EBO, textureID;
	std::vector<float> vertices;
	std::vector<GLuint> indices;
	std::string texturePath;
private:
	void setVertices();
public:
	Sprite() = default;
	Sprite(glm::vec2 position, const char* path);
public:
	void draw();
	void update(int x, int y);
};

