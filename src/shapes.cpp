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
            -0.5f, -0.5f, // left  
            0.5f, -0.5f, // right 
            0.0f,  0.5f // top   
        },
        {
            0, 1, 2
        })
{
}

Rect::Rect()
    : shape({
            -0.5f, -0.5f, 
            0.5f, -0.5f,
            0.0f,  0.6f, 
            0.3f,  0.4f
        },
        {
            0, 1, 2,
            1, 2, 3
        })
{
}




