#pragma once

#include "../includes.h"
#include "../renderer/renderer.h"

class Window {
public:
	GLFWwindow* glfw_window;
	int width;
	int height;
	std::string title;
	bool closed;

	Window(int width, int height, std::string title);
	void swap();
	~Window();
};