#pragma once

class vao
{
public:
	vao();

	void bind() const;

	void unbind() const;

	~vao();
private:
	unsigned m_id;
};

