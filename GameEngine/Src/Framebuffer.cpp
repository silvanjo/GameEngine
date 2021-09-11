#include "Framebuffer.h"



Framebuffer::Framebuffer(unsigned int width, unsigned int height)
{
	Framebuffer::width  = width;
	Framebuffer::height = height;

	glGenFramebuffers(1, &ID);

	// Create Texture for the framebuffer
	glGenTextures(1, &(Framebuffer::texture));
	glBindTexture(GL_TEXTURE_2D, Framebuffer::texture);

	// Allocate memory for framebuffer
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);

	// Attach color-texture to framebuffer 
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, Framebuffer::texture, 0);

	// Allocate memory for depth and stencil buffer
	glTexImage2D(
		GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0,
		GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr
	);

	// Attach depth and stencil-buffer to the framebuffer
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, texture, 0);
}


Framebuffer::~Framebuffer()
{
	glDeleteFramebuffers(1, &ID);
}

void Framebuffer::Bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, ID);
}

void Framebuffer::Unbind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

// Returns true of the framebuffer is complete
bool Framebuffer::Complete() {
	return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}