#pragma once

#include <GL/glew.h>

#include "VBO.h"
#include "EBO.h"

class VAO
{

public:
	VAO();
	~VAO();

	GLuint ID;

	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	void Bind();
	void Unbind();

};

