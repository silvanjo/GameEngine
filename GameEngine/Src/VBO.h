#pragma once

#include <GL/glew.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <vector>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texUV;
};

class VBO
{
public:
	GLuint ID;
	VBO();
	VBO(std::vector<Vertex>& vertices);
	~VBO();

	void CreateVBO(std::vector<Vertex>& vertices);

	void Bind();
	void Unbind();
};

