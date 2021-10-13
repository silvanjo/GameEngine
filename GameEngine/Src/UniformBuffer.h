#pragma once

#include <GL/glew.h>
#include <map>

class UniformBuffer
{
public:
	UniformBuffer();
	UniformBuffer(unsigned int data_size);
	~UniformBuffer();

	void Bind();
	void UnBind();

	void CreateUniformBuffer(unsigned int data_size);

	void BindBufferRange(unsigned int index, unsigned int offset, unsigned int data_size);

	void BufferSubData(unsigned int offset, unsigned int data_size, void* data);

	std::pair<unsigned int, unsigned int>* GetBufferRange(unsigned int index);

private:
	GLuint ID;
	std::map<unsigned int, std::pair<unsigned int, unsigned int>> indices;
};