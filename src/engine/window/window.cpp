#include "window.h"

Window::Window(int width, int height, std::string title) {
	if (!glfwInit()) {
		std::cout << "ERROR: Unable to initalize glfw" << std::endl;
	}

	this->width = width;
	this->height = height;
	this->title = title;

	this->glfw_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

	if (!this->glfw_window) {
		std::cout << "ERROR: Cannot initialize glfw window" << std::endl;
		glfwTerminate();
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwMakeContextCurrent(this->glfw_window);
	if (glewInit() == GLEW_OK) {
		std::cout << "INFO: Initalized glew" << std::endl;
	}
	else {
		std::cout << "ERROR: Cannot initialize glew" << std::endl;
	}
	this->closed = glfwWindowShouldClose(this->glfw_window);
	glc(glEnable(GL_BLEND));
	glc(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

}

void Window::swap() {
	this->closed = glfwWindowShouldClose(this->glfw_window);
	glfwSwapBuffers(this->glfw_window);
	glfwPollEvents();
}

Window::~Window(){
	glfwTerminate();
}