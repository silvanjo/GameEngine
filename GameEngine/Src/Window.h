#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

class Window {
public:
	Window(int width, int height, const std::string& title);
	~Window();

	int getWidth() const;
	int getHeight() const;

	bool windowShouldClose();

	GLFWwindow* getWindow();

	void swapBuffers();
	void pollEvents();

	void closeIfKeyisPressed(int key);

	void clear();
	void clear(float v1, float v2, float v3, float alpha);

private:
	GLFWwindow* window;
	int width, height;
};