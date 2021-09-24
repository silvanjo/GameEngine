#pragma once

#include <GL/glew.h>

class Framebuffer
{
public:
	Framebuffer(unsigned int width, unsigned int height);
	~Framebuffer();

	void BindFramebuffer();
	void UnbindFramebuffer();

	void BindColorTexture();
	void UnBindColorTexture();

	bool IsComplete();

	GLenum GetFramebufferStatus();

private:
	GLuint ID;
	GLuint color_texture;			// color attachment
	GLuint render_buffer;			// buffer for depth and stencil data

	unsigned int width;
	unsigned int height;
};

