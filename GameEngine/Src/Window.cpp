#include "Window.h"

#include "Camera.h"

Window::Window(int width, int height, const std::string& title) : 
	width(width), height(height)
{
	if (!glfwInit())
		std::cout << "Failed to create window" << std::endl;

	window = glfwCreateWindow(width, height, "Blending Demo", NULL, NULL);
	if (!window)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		std::cout << "Initialization of OpenGL failed" << std::endl;

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, Camera::mouse_callback);
	
	// Enable Depth-testing
	glEnable(GL_DEPTH_TEST);

	// Blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDepthFunc(GL_LEQUAL);

	// Enable face-culling (counter-clockwise vertices are front-faces)
	// glEnable(GL_CULL_FACE);
	// glCullFace(GL_FRONT);

	// Print the current OpenGl version
	std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
}

Window::~Window() {
	glfwTerminate();
}

int Window::getWidth() const {
	return this->width;
}

int Window::getHeight() const {
	return this->height;
}

bool Window::windowShouldClose() {
	return glfwWindowShouldClose(window);
}

GLFWwindow* Window::getWindow() {
	return this->window;
}

void Window::closeIfKeyisPressed(int key) {
	if(glfwGetKey(window, key) == GLFW_PRESS) 
		glfwTerminate();
}

void Window::swapBuffers() {
	glfwSwapBuffers(window);
}

void Window::pollEvents() {
	glfwPollEvents();
}

void Window::clear() {
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Window::clear(float v1, float v2, float v3, float alpha) {
	glClearColor(v1, v2, v3, alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}