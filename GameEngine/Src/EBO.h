#pragma once

#include <GL/glew.h>

#include <vector>

class EBO
{
public:
	EBO(std::vector<GLuint>& indices);
	~EBO();

	GLuint ID;

	void Bind();
	void Unbind();
};

