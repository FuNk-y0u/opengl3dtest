#include "vertex_attrib_array.h"

VertexAttribLayout::VertexAttribLayout() {
}

void VertexAttribLayout::push(unsigned int id, unsigned int count, unsigned int type, bool normalized) {
	VertexAttribElement element = { id, count, type, normalized};
	elements.push_back(element);
}

void VertexAttribLayout::bind() {
	int length = elements.size();
	unsigned int stride = 0;
	unsigned int offset = 0;

	std::list<VertexAttribElement> elements2;

	for (int i = 0; i < (length); i++) {
		VertexAttribElement element = elements.front();
		elements2.push_back(element);
		stride += sizeof(element.type) * element.count;
		elements.pop_front();
	}

	for (int i = 0; i < (length); i++) {
		VertexAttribElement element = elements2.front();
		elements2.pop_front();
		
		glc(glEnableVertexAttribArray(element.id));
		glc(glVertexAttribPointer(element.id, element.count,element.type, element.normalized ? GL_TRUE : GL_FALSE, stride,(const void*) offset));

		offset += element.count * sizeof(element.type);
		
	}
	
}
