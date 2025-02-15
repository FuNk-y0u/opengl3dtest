#include "index_buffer.h"


IndexBuffer::IndexBuffer(const void* data, unsigned int size, bool draw_dynamic) {
	unsigned int index_buffer;
	glc(glGenBuffers(1, &index_buffer));
	glc(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer));
	glc(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, draw_dynamic?GL_DYNAMIC_DRAW:GL_STATIC_DRAW));
	this->id = index_buffer;
}

void IndexBuffer::bind() {
	glc(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id));
}

void IndexBuffer::unbind() {
	glc(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

IndexBuffer::~IndexBuffer() {
	glc(glDeleteBuffers(1, &this->id));
}