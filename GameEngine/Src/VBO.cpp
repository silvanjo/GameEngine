#include "VBO.h"

VBO::VBO()
{

}

VBO::VBO(std::vector<Vertex>& vertices) 
{
	CreateVBO(vertices);
}

VBO::~VBO() {
	glDeleteBuffers(1, &ID);
}

void VBO::CreateVBO(void* data, unsigned int data_size)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, data_size, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::CreateVBO(std::vector<Vertex>& vertices)
{
	CreateVBO((void*) vertices.data(), vertices.size() * sizeof(Vertex));
}

void VBO::CreateVBO(unsigned int buffer_size)
{
	// data is set to 0
	CreateVBO(0, buffer_size);
}

void VBO::SetBufferSubData(void* data, unsigned int offset, unsigned int data_size)
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferSubData(GL_ARRAY_BUFFER, offset, data_size, data);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::SetBufferSubData(std::vector<Vertex>& vertices, unsigned int offset)
{
	SetBufferSubData(vertices.data(), offset, vertices.size() * sizeof(Vertex));
}

void* VBO::GetBufferPointer()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	return glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
}

bool VBO::UnmapBufferPointer()
{
	return glUnmapBuffer(GL_ARRAY_BUFFER);
}

void VBO::Bind() 
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind() 
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}