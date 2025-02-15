#pragma once

#include "../includes.h"

class IndexBuffer {
public:
	unsigned int id;
	IndexBuffer(const void* data, unsigned int size, bool draw_dynamic = true);
	~IndexBuffer();
	void bind();
	void unbind();
};