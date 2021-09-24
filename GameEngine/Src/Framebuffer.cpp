#include "Framebuffer.h"



Framebuffer::Framebuffer(unsigned int width, unsigned int height)
{
	Framebuffer::width  = width;
	Framebuffer::height = height;

	glGenFramebuffers(1, &ID);

	BindFramebuffer();

	// Create and attach color buffer

		// Create Texture for the framebuffer
		glGenTextures(1, &(Framebuffer::color_texture));
		glBindTexture(GL_TEXTURE_2D, Framebuffer::color_texture);

		// Allocate memory for color buffer
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Attach color-texture to framebuffer 
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_texture, 0);

		glBindTexture(GL_TEXTURE_2D, 0);
	
	
	// ----------------------------------

	// Create and attach depth and stencil buffer

		glGenRenderbuffers(1, &render_buffer);
		glBindRenderbuffer(GL_RENDERBUFFER, render_buffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);									// Allocate memory for the renderbuffer

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, render_buffer);		// Attach renderbuffer to the currently bound framebuffer

		glBindRenderbuffer(GL_RENDERBUFFER, 0);

	// ----------------------------------

	UnbindFramebuffer();
	
}


Framebuffer::~Framebuffer()
{
	glDeleteFramebuffers(1, &ID);
}

void Framebuffer::BindFramebuffer() {
	glBindFramebuffer(GL_FRAMEBUFFER, ID);
}

void Framebuffer::UnbindFramebuffer() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::BindColorTexture()
{
	glBindTexture(GL_TEXTURE_2D, color_texture);
}

void Framebuffer::UnBindColorTexture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

// Returns true of the framebuffer is complete
bool Framebuffer::IsComplete() {
	BindFramebuffer();
	bool complete = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
	UnbindFramebuffer();
	return complete;
}

GLenum Framebuffer::GetFramebufferStatus()
{
	return glCheckFramebufferStatus(GL_FRAMEBUFFER);
}