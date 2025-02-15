#include "shader.h"


unsigned int Shader::create_shader(unsigned int shader_type) {
	return glc(glCreateShader(shader_type));
}

void Shader::compile_shader(char* shader, unsigned int id, unsigned int type) {
	glc(glShaderSource(id, 1, &shader, NULL));
	glc(glCompileShader(id));
	int result, length;

	glc(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE) {
		glc(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));
		glc(glGetShaderInfoLog(id, length, &length, message));
		if (type == GL_VERTEX_SHADER) {
			std::cout << "ERROR: Failed to compile vertex shader" << std::endl;
		}
		else {
			std::cout << "ERROR: Failed to compile fragment shader" << std::endl;
		}
		printf("%s\n", message);
		free(message);
		glc(glDeleteShader(id));
	}
}

Shader::Shader(const char* vertex_shader, const char* fragment_shader) {
	unsigned int program;
	unsigned int vert_shader;
	unsigned int frag_shader;

	program = glCreateProgram();

	vert_shader = create_shader(GL_VERTEX_SHADER);
	frag_shader = create_shader(GL_FRAGMENT_SHADER);

	compile_shader((char*)vertex_shader, vert_shader, GL_VERTEX_SHADER);
	compile_shader((char*)fragment_shader, frag_shader, GL_VERTEX_SHADER);

	glc(glAttachShader(program, vert_shader));
	glc(glAttachShader(program, frag_shader));
	glc(glLinkProgram(program));
	glc(glValidateProgram(program));

	glc(glDeleteShader(vert_shader));
	glc(glDeleteShader(frag_shader));

	glc(glUseProgram(program));

	this->id = program;
}

void Shader::bind() {
	glc(glUseProgram(this->id));
}

void Shader::unbind() {
	glc(glUseProgram(0));
}

void Shader::uniformmat4f(const char* variable_name, const glm::mat4& data, int count) {
	int uniform_location = glc(glGetUniformLocation(this->id, variable_name));
	if (uniform_location == -1) {
		std::cout << "ERROR: Cannot find uniform location" << std::endl;
	}
	glc(glUniformMatrix4fv(uniform_location, count, GL_FALSE, &data[0][0]));
}

void Shader::uniform1iv(const char* variable_name, const int* data, int count) {
	int uniform_location = glc(glGetUniformLocation(this->id, variable_name));
	if (uniform_location == -1) {
		std::cout << "ERROR: Cannot find uniform location" << std::endl;
	}
	glc(glUniform1iv(uniform_location, count, data));
}
Shader::~Shader() {

}

