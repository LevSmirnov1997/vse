#pragma once
#include <vector>

class buffer
{
public:
	buffer(unsigned target, const void* data, unsigned size);

	void bind() const;

	void vertex_atrrib_pointer(int index, int stride, unsigned type) const;

	void unbind() const;

	~buffer();

private:
	unsigned m_id;
	unsigned m_type;
	unsigned m_size;
};
