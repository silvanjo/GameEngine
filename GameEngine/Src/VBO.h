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

	//
	// Creates vertex buffer and fills it with data
	//
	void CreateVBO(void* data, unsigned int data_size);
	void CreateVBO(std::vector<Vertex>& vertices);
	//
	// Creates an empty Vertex buffer with size buffer_size bytes
	//
	void CreateVBO(unsigned int buffer_size);
	//
	// Set data at a specified offset of size data_size bytes
	//
	void SetBufferSubData(void* data, unsigned int offset, unsigned int data_size);
	void SetBufferSubData(std::vector<Vertex>& vertices, unsigned int offset);
	//
	// Returns a pointer to the buffer
	// If this method is used it is neccessary to call UnmapBufferPointer if the pointer is not in use anymore
	// The method also binds the buffer to GL_ARRAY_BUFFER without unbinding it
	//
	void* GetBufferPointer();
	//
	// Has to be called if the pointer returned by GetBufferPointer is not longer in use
	// After this method was called the pointer is not longer valid
	// The method returns true if OpenGL was able to write the data into the buffer
	//
	bool UnmapBufferPointer();

	void Bind();
	void Unbind();
};

