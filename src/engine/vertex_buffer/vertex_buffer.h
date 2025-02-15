#pragma once
#include "../includes.h"
class VertexBuffer {
public:
	unsigned int id;

	VertexBuffer(const void* data, unsigned int size, bool draw_dynamic = true);
	void bind();
	void unbind();
	~VertexBuffer();
};



