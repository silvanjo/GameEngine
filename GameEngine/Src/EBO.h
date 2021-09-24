#pragma once

#include <GL/glew.h>

#include <vector>

class EBO
{
public:
	EBO();
	EBO(std::vector<GLuint>& indices);
	~EBO();

	GLuint ID;

	void CreateEBO(std::vector<GLuint>& indices);

	void Bind();
	void Unbind();
};

