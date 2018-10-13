#include "buffer.hpp"
#include <glad/glad.h>

buffer::buffer(unsigned target, const void* data, unsigned size)
	: m_type(target),
	  m_size(size)
{
	glGenBuffers(1, &m_id);
	this->bind();
	glBufferData(target, m_size, data, GL_DYNAMIC_DRAW);
	this->unbind();
}

void buffer::vertex_atrrib_pointer(int index, int stride, unsigned type) const
{
	glVertexAttribPointer(index, 2, type, GL_FALSE, stride, (void*)0);
	glEnableVertexAttribArray(index);
}

void buffer::bind() const
{ 
	glBindBuffer(m_type, m_id);
}

void buffer::unbind() const
{
	glBindBuffer(m_type, 0);
}

buffer::~buffer()
{
	glDeleteBuffers(1, &m_id);
}
