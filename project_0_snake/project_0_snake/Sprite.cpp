#include "Sprite.h"

#include <iostream>
#include "Globals.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

std::string vertex_shader_source_sprite = R"(
	#version 330 core
	
	layout(location = 0) in vec4 vertex;
	

	
	out vec2 TexCoords;

	uniform mat4 model;
	uniform mat4 projection;

	void main()
	{
		TexCoords = vertex.zw;
		gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
		
		
	}	

)";


std::string fragment_shader_source_sprite = R"(
	#version 330 core
	
	
	in vec2 TexCoords;

	out vec4 color;

	uniform sampler2D image;

	void main() {
		color = texture(image, TexCoords);
	}
)";

void Sprite::setVertices()
{
	int x = position.x;
	int y = position.y;
	
	vertices = {
		// pos      // tex
		 0.0f, 1.0f, 0.0f, 1.0f,
		 1.0f, 0.0f, 1.0f, 0.0f,
		 0.0f, 0.0f, 0.0f, 0.0f,

		 0.0f, 1.0f, 0.0f, 1.0f,
		 1.0f, 1.0f, 1.0f, 1.0f,
		 1.0f, 0.0f, 1.0f, 0.0f
		
	};

	//vertices = {
	//	// positions          // colors           // texture coords
	//	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
	//	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
	//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
	//	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	//};

	//indices = {
	//	0,1,3, // First Triangle
	//	1,2,3 // Second Triangle
	//};

	//indices = {
	//	  0, 1, 3, // first triangle
	//	1, 2, 3  // second triangle
	//};
}

Sprite::Sprite(glm::vec2 position, const char* path) : shader(vertex_shader_source_sprite, fragment_shader_source_sprite)
{
	texturePath = std::string(path);
	this->position = position;

	setVertices();

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//// color attribute
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);
	// texture coord attribute
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	//glEnableVertexAttribArray(1);

	// Load and create texture
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
	if (data){
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else{
		std::cout << "Failed to load texture" << std::endl;
		exit(-1);
	}
	stbi_image_free(data);

	model = glm::mat4(1.0f);
	//view = glm::mat4(1.0f);
	projection = glm::mat4(1.0f);

	projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);

	std::cout << "Loaded Texture successfully ...\n";

	
}

void Sprite::draw() {

	shader.use();
	
	

	
	model = glm::translate(model, glm::vec3(position, 0.0f));

	model = glm::translate(model, glm::vec3(0.5f * width, 0.5f * height, 0.0f));
	//model = glm::rotate(model, glm::radians(0), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * width, -0.5f * height, 0.0f));

	model = glm::scale(model, glm::vec3(glm::vec2(width,height), 1.0f));

	shader.uploadMatrix4f("model", model);
	//shader.uploadMatrix4f("uView", view);
	shader.uploadMatrix4f("projection", projection);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glBindVertexArray(VAO);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

}

void Sprite::update(int x, int y) {
	this->position = glm::vec2(x, y);
	setVertices();
	// https://stackoverflow.com/questions/72633347/glbuffersubdata-not-working-doesnt-show-error
	// WE bind it before so it works
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() *  sizeof(float), &vertices[0]);
}
