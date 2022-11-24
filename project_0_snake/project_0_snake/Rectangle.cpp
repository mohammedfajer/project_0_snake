#include "Rectangle.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Globals.h"
#include <iostream>

std::string vertex_shader_source = R"(
	#version 330 core
	
	layout(location = 0) in vec3 aPos;
	layout(location = 1) in vec4 aColor;

	out vec4 fColor;

	uniform mat4 uModel;
	uniform mat4 uView;
	uniform mat4 uProjection;

	void main()
	{
		fColor = aColor;
		gl_Position = uProjection * uView * uModel *  vec4(aPos, 1.0);
	}	

)";


std::string fragment_shader_source = R"(
	#version 330 core
	
	in vec4 fColor;
	out vec4 color;

	void main() {
		color = fColor;
	}
)";

Rectangle::Rectangle(int x, int y, int width, int height, Color c, int mode)
	: shader(vertex_shader_source, fragment_shader_source), c(c), mode(mode) {
	this->x = x;
	this->y = y;
	this->width = width; 
	this->height = height;
	position = glm::vec2(x, y);


	if (mode == DRAW_MODE_OUTLINE) {
		indices = { 0,1,3,2 };
	}
	else {
		indices = { 0,2,1, 1,2,3 };
	}

	set_vertices();

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	// Position Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Color Attribute
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	model = glm::mat4(1.0f);
	view = glm::mat4(1.0f);
	//view = glm::translate(view, glm::vec3(10.0f, 200.0f, 0.0f));

	//projection = glm::perspective(glm::radians(45.0f), (float) SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);
	projection = glm::ortho(0.0f, (float)SCR_WIDTH, (float)SCR_HEIGHT, 0.0f , -1.0f, 1.0f);
	mode = DRAW_MODE_FILLED;
}

void Rectangle::set_vertices() {
	// Top left 0, 1, 2
	vertices[0] = (float)x;
	vertices[1] = (float)y;
	vertices[2] = 0.0f;

	// Color (1) 3,4,5,6
	vertices[3] = c.r;
	vertices[4] = c.g;
	vertices[5] = c.b;
	vertices[6] = c.a;

	// Top Right 7, 8, 9
	vertices[7] = (float)(x + width);
	vertices[8] = (float)y;
	vertices[9] = 0.0f;

	// Color (2) 10,11,12,13
	vertices[10] = c.r;
	vertices[11] = c.g;
	vertices[12] = c.b;
	vertices[13] = c.a;

	// Bottom Left 14, 15, 16
	vertices[14] = (float)x;
	vertices[15] = (float)(y + height);
	vertices[16] = 0.0f;

	// Color (3) 17,18,19,20
	vertices[17] = c.r;
	vertices[18] = c.g;
	vertices[19] = c.b;
	vertices[20] = c.a;

	// Bottom Right 21,22,23
	vertices[21] = (float)(x + width);
	vertices[22] = (float)(y + height);
	vertices[23] = 0.0f;

	// Color (4) 24,25,26,27
	vertices[24] = c.r;
	vertices[25] = c.g;
	vertices[26] = c.b;
	vertices[27] = c.a;
}


void Rectangle::draw() {
	shader.use();
	shader.uploadMatrix4f("uModel", model);
	shader.uploadMatrix4f("uView", view);
	shader.uploadMatrix4f("uProjection", projection);
	glBindVertexArray(VAO);

	
	if (mode == DRAW_MODE_OUTLINE) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, 0);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
	

	
	/*glBindVertexArray(0);
	shader.unbind();*/
}

void Rectangle::setThickness(int thickenss) {
	glLineWidth(thickenss);
}

void Rectangle::update(int x, int y) {
	this->x = x;
	this->y = y;
	set_vertices();
	// https://stackoverflow.com/questions/72633347/glbuffersubdata-not-working-doesnt-show-error
	// WE bind it before so it works
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	
}

