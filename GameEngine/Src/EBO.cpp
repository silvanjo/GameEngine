#include "EBO.h"

EBO::EBO()
{

}

EBO::EBO (std::vector<GLuint>& indices) 
{
	CreateEBO(indices);
}

EBO::~EBO () 
{
	glDeleteBuffers(1, &ID);
}

void EBO::CreateEBO(std::vector<GLuint>& indices)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Bind() 
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::Unbind() 
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}