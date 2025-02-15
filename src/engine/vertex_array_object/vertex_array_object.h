#pragma once
#include "../includes.h"

class VertexArrayObject {
public:
	unsigned int id;

	VertexArrayObject();
	void bind();
	void unbind();
	~VertexArrayObject();
	
};