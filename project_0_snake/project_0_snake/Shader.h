#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	Shader() = default;
	Shader(std::string v, std::string f);
	void use();
	void unbind();
	void uploadMatrix4f(std::string name, glm::mat4 m);
	void uploadVec3f(std::string name, glm::vec3 v);
private:
	void compileShader();
	void compileProgram();
public:
	GLuint shader_program;
private:
	GLuint vertex_shader_ID;
	GLuint fragment_shader_ID;
	std::string vertex_shader_source;
	std::string fragment_shader_source;
};

