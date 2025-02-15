#pragma once
#include "../includes.h"

class Shader {
private:
	unsigned int create_shader(unsigned int shader_type);
	void compile_shader(char* shader, unsigned int id, unsigned int type);
public:
	unsigned int id;
	Shader(const char* vertex_shader, const char* fragment_shader);
	void bind();
	void unbind();
	void uniformmat4f(const char* variable_name, const glm::mat4& data, int count);
	void uniform1iv(const char* variable_name, const int* data, int count);
	~Shader();
};