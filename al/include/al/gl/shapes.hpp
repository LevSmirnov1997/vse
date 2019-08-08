#pragma once
#include "vao.hpp"
#include <vector>

class shape
{
public:
    enum class shape_type
    {
        triangle = 0,
        rectangle
    };

	shape(const std::vector<float> &v, const std::vector<unsigned> &i);

	void bind() const { m_vao.bind(); }

	unsigned size() const { return m_size;  }

    virtual shape_type type() const = 0;

	virtual ~shape() { }

private:
	vao m_vao;
	unsigned m_size;
};

class Triangle : public shape
{
public:
	Triangle();

    virtual shape_type type() const override { return shape_type::triangle; }
};

class Rect: public shape
{
public:
	Rect();

    virtual shape_type type() const override { return shape_type::rectangle; }
};

static const std::vector<float> TriangleVerticies = {
			-50.f, 50.f, // left
			 50.f, 50.f, // right
			 0.f, -50.0f // top
};

static const std::vector<float> RectangleVerticies = {
            -50.f,   50.f,
             50.f,  -50.f,
            -50.f,  -50.f,
             50.f,   50.f
};

