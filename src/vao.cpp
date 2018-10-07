#include "vao.hpp"
#include <glad/glad.h>

vao::vao()
{
	glGenVertexArrays(1, &m_id);
}

void vao::bind() const
{
	glBindVertexArray(m_id);
}

void vao::unbind() const
{
	glBindVertexArray(0);
}

vao::~vao()
{
	glDeleteVertexArrays(1, &m_id);
}

