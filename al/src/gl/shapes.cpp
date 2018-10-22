#include "shapes.hpp"
#include "buffer.hpp"
#include <glad/glad.h>

shape::shape(const std::vector<float> &v, const std::vector<unsigned> &i)
		: m_size(v.size())
	{
		m_vao.bind();
		buffer vbo(GL_ARRAY_BUFFER, v.data(), sizeof(float) * v.size());
		buffer ebo(GL_ELEMENT_ARRAY_BUFFER, i.data(), sizeof(unsigned) * i.size());
		vbo.bind();
		ebo.bind();
		vbo.vertex_atrrib_pointer(0, 2 * sizeof(float), GL_FLOAT);
		m_vao.unbind();
	}

Triangle::Triangle()
    : shape({
			-50.f, 50.f, // left
			 50.f, 50.f, // right
			 0.f, -50.0f // top
        },
        {
            0, 1, 2
        })
{
}

Rect::Rect()
    : shape({
            -50.f,   50.f, 
             50.f,  -50.f,
            -50.f,  -50.f,
             50.f,   50.f
        },
        {
            0, 1, 2,
            1, 0, 3
        })
{
}




