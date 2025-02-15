#include "vertex_array_object.h"

VertexArrayObject::VertexArrayObject() {
	unsigned int vertex_array_object;

	glc(glGenVertexArrays(1, &vertex_array_object));
	glc(glBindVertexArray(vertex_array_object));

	this->id = vertex_array_object;
}

void VertexArrayObject::bind() {
	glc(glBindVertexArray(this->id));
}

void VertexArrayObject::unbind() {
	glc(glBindVertexArray(0));
}

VertexArrayObject::~VertexArrayObject() {
	glc(glDeleteBuffers(1, &this->id));
}