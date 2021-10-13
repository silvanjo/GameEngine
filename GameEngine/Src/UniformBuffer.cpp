#include "UniformBuffer.h"

UniformBuffer::UniformBuffer()
{

}

UniformBuffer::UniformBuffer(unsigned int data_size)
{
	CreateUniformBuffer(data_size);
}

UniformBuffer::~UniformBuffer()
{
	glDeleteBuffers(1, &ID);
}

void UniformBuffer::Bind()
{
	glBindBuffer(GL_UNIFORM_BUFFER, ID);
}

void UniformBuffer::UnBind()
{
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBuffer::CreateUniformBuffer(unsigned int data_size)
{
	glGenBuffers(1, &ID);
	
	glBindBuffer(GL_UNIFORM_BUFFER, ID);
	glBufferData(GL_UNIFORM_BUFFER, data_size, nullptr, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBuffer::BindBufferRange(unsigned int index, unsigned int offset, unsigned int data_size)
{
	indices.insert({ index, std::pair<unsigned int, unsigned int>(offset, offset + data_size) });
	
	glBindBufferRange(GL_UNIFORM_BUFFER, index, ID, offset, data_size);
}

void UniformBuffer::BufferSubData(unsigned int offset, unsigned int data_size, void* data)
{
	glBindBuffer(GL_UNIFORM_BUFFER, ID);
	glBufferSubData(GL_UNIFORM_BUFFER, offset, data_size, data);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

std::pair<unsigned int, unsigned int>* UniformBuffer::GetBufferRange(unsigned int index)
{
	if (indices.count(index))
		return &indices[index];

	return nullptr;
}