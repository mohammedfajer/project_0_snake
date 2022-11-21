#include "Shader.h"
#include <iostream>

Shader::Shader(std::string v, std::string f) {
	vertex_shader_source = v;
	fragment_shader_source = f;
	compileProgram();
}

void Shader::use() {
	if (shader_program != 0) {
		glUseProgram(shader_program);
	}
	
}

void Shader::uploadMatrix4f(std::string name, glm::mat4 m) {
	glUniformMatrix4fv(glGetUniformLocation(shader_program, name.c_str()), 1, GL_FALSE, glm::value_ptr(m));
}

void Shader::uploadVec3f(std::string name, glm::vec3 v) {
	glUniform3fv(glGetUniformLocation(shader_program, name.c_str()), 1, glm::value_ptr(v));
}

void Shader::compileShader() {
	vertex_shader_ID = glCreateShader(GL_VERTEX_SHADER);
	const char* c = vertex_shader_source.c_str();
	glShaderSource(vertex_shader_ID, 1, &c, NULL);
	glCompileShader(vertex_shader_ID);

	int  success;
	char infoLog[512];
	glGetShaderiv(vertex_shader_ID, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vertex_shader_ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		exit(-1);
	}

	fragment_shader_ID = glCreateShader(GL_FRAGMENT_SHADER);
	c = fragment_shader_source.c_str();
	glShaderSource(fragment_shader_ID, 1, &c, NULL);
	glCompileShader(fragment_shader_ID);

	glGetShaderiv(fragment_shader_ID, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(fragment_shader_ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		exit(-1);
	}
}

void Shader::compileProgram() {
	compileShader();
	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader_ID);
	glAttachShader(shader_program, fragment_shader_ID);
	glLinkProgram(shader_program);
	glUseProgram(shader_program);
	glDeleteShader(vertex_shader_ID);
	glDeleteShader(fragment_shader_ID);
}
