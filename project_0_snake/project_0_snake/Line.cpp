#include "Line.h"
#include "Globals.h"

std::string vertex_shader_source_line = R"(
	#version 330 core
	
	layout(location = 0) in vec3 aPos;

	uniform mat4 uModel;
	uniform mat4 uView;
	uniform mat4 uProjection;
	

	void main()
	{
		gl_Position = uProjection * uView * uModel *  vec4(aPos, 1.0);
	}	

)";


std::string fragment_shader_source_line = R"(
	#version 330 core
	
	uniform vec3 uColor;
	out vec4 color;

	void main() {
		color = vec4(uColor,1);
	}
)";

Line::Line(glm::vec2 startPoint, glm::vec2 endPoint, Color color)
	: shader(vertex_shader_source_line, fragment_shader_source_line), lineColor(color)
{
	this->startPoint = startPoint;
	this->endPoint = endPoint;

	vertices = { startPoint.x, startPoint.y, 0.0f,
				 endPoint.x	 , endPoint.y  , 0.0f };

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	model = glm::mat4(1.0f);
	view = glm::mat4(1.0f);
	projection = glm::ortho(0.0f, (float)SCR_WIDTH, (float)SCR_HEIGHT, 0.0f, -1.0f, 1.0f);
}

void Line::Draw()
{
	glLineWidth(thickness);
	shader.use();
	shader.uploadMatrix4f("uModel", model);
	shader.uploadMatrix4f("uView", view);
	shader.uploadMatrix4f("uProjection", projection);
	shader.uploadVec3f("uColor", glm::vec3(lineColor.r, lineColor.g, lineColor.b));
	glBindVertexArray(VAO);
	glDrawArrays(GL_LINES, 0, 2);
	glBindVertexArray(0);
	glLineWidth(0);
}

void Line::setThickness(int thickness)
{
	this->thickness = thickness;
	
}
