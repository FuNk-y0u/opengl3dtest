#pragma once
#include "../includes.h"

struct VertexAttribElement {
	unsigned int id;
	unsigned int count;
	unsigned int type;
	bool normalized;
};


class VertexAttribLayout {
private:
	std::list<VertexAttribElement> elements;
public:
	unsigned int id;

	VertexAttribLayout();

	void push(unsigned int id, unsigned int count, unsigned int type,bool normalized = false);

	void bind();
};