#pragma once
#include "vao.hpp"
#include <vector>

class shape
{
public:

	shape(const std::vector<float> &v, const std::vector<unsigned> &i);

	void bind() const { m_vao.bind(); }

	unsigned size() const { return m_size;  }

	virtual ~shape() { }

private:
	vao m_vao;
	unsigned m_size;
};

class Triangle : public shape
{
public:
	Triangle();
};

class Rect: public shape
{
public:
	Rect();
};





