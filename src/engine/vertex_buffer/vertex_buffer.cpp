#include "vertex_buffer.h"


VertexBuffer::VertexBuffer(const void* data, unsigned int size, bool draw_dynamic) {
	unsigned int vertex_buffer;

	glc(glGenVertexArrays(1, &vertex_buffer));
	glc(glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer));
	glc(glBufferData(GL_ARRAY_BUFFER, size, data, draw_dynamic? GL_DYNAMIC_DRAW: GL_STATIC_DRAW));

	this->id = vertex_buffer;
}

void VertexBuffer::bind() {
	glc(glBindBuffer(GL_ARRAY_BUFFER, this->id));
}

void VertexBuffer::unbind() {
	glc(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

VertexBuffer::~VertexBuffer() {
	glc(glDeleteBuffers(1, &this->id));
}

