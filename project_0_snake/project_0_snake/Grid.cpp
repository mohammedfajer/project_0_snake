#include "Grid.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Globals.h"
#include <iostream>


std::string vertex_shader_source_grid = R"(
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


std::string fragment_shader_source_grid = R"(
	#version 330 core
	
	
	out vec4 color;

	void main() {
		color = vec4(196/255.0, 189/255.0, 120/255.0,1);
	}
)";

Grid::Grid() 
	: shader(vertex_shader_source_grid, fragment_shader_source_grid) {

	

	set_vertices();


	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * 3 * sizeof(float), &vertices[0], GL_STATIC_DRAW);


	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * 3 * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	// Position Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	model = glm::mat4(1.0f);
	view = glm::mat4(1.0f);
	//view = glm::translate(view, glm::vec3(10.0f, 200.0f, 0.0f));

	//projection = glm::perspective(glm::radians(45.0f), (float) SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);
	projection = glm::ortho(0.0f, (float)SCR_WIDTH, (float)SCR_HEIGHT, 0.0f, -1.0f, 1.0f);
}

void Grid::setThickness(int thickness) {
	glLineWidth(thickness);
	glPointSize(thickness);
	this->thickness = thickness;
}

void Grid::setColor(Color c) {
	this->color = c;
}

void Grid::draw() {
	shader.use();
	shader.uploadMatrix4f("uModel", model);
	shader.uploadMatrix4f("uView", view);
	shader.uploadMatrix4f("uProjection", projection);
	glBindVertexArray(VAO);

	GLuint lenght = (GLuint)indices.size() * 3;

	glDrawElements(GL_LINES, lenght, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void Grid::set_vertices(){

	glLineWidth(0.2);
	vertices.push_back(glm::vec3(16, 0, 0));
	vertices.push_back(glm::vec3(0, 16, 0));
	vertices.push_back(glm::vec3(0, 32, 0));

	indices.push_back(glm::uvec3(0, 1, 2));
}

