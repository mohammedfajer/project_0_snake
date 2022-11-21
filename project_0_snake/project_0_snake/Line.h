#pragma once

#include "Shader.h"
#include "Color.h"
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Line
{
public:
	Line(glm::vec2 startPoint, glm::vec2 endPoint, Color color);
	void Draw();
	void setThickness(int thickness);
private:
	Shader shader;
	GLuint VBO, VAO;
	std::vector<float> vertices;
	glm::vec2 startPoint;
	glm::vec2 endPoint;
	glm::mat4 model, view, projection;
	Color lineColor;
	int thickness;
};

