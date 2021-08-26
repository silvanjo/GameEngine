#pragma once

#include <GL/glew.h>

class Framebuffer
{
public:
	Framebuffer(unsigned int width, unsigned int height);
	~Framebuffer();

	void Bind();
	void Unbind();

	bool Complete();

private:
	GLuint ID;
	GLuint texture;

	unsigned int width;
	unsigned int height;
};

