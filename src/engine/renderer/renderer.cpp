#include "renderer.h"

void drawcall(unsigned int count) {
	glc(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, NULL));
}

void clear_color_buffer() {
	
	glc(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	glc(glClearColor(0.529f, 0.808f, 0.922f, 1.0f));
}