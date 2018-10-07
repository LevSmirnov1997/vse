#include "program.hpp"
#include <glad/glad.h>

program::program()
	: m_id(glCreateProgram())
{

}

program::program(program &&temp)
	: m_id(std::move(temp.m_id))
{
	temp.m_id = ~0u;
}

program& program::operator=(program &&temp)
{
	this->m_id = temp.m_id;
	temp.m_id = ~0u;
	return *this;
}

program::~program()
{
	if (this->valid())
		glDeleteProgram(m_id);
}

void program::attach_shader(const shader &s) const
{
	glAttachShader(m_id, s.id());
}

void program::detach_shader(const shader &s) const
{
	glDetachShader(m_id, s.id());
}

bool program::link() const
{
	glLinkProgram(m_id);
	GLint success;
	glGetProgramiv(m_id, GL_LINK_STATUS, &success);
	return success != 0;
}

void program::use() const
{
	glUseProgram(m_id);
}

void program::unuse() const
{
	glUseProgram(0);
}

bool program::valid() const
{
	return glIsProgram(m_id);
}

std::string program::info_log() const
{
	GLint size = 0;
	glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &size);
	if (0 == size)
		return "";

	std::string info;
	info.resize(size);
	glGetProgramInfoLog(m_id, size, nullptr, &info[0]);
	return info;
}

program program::create_progarm(const std::vector<shader_args> &&args)
{
	program p;
	for (const auto &arg : args)
		p.attach_shader({ arg.first, arg.second });
	p.link();
	return p;
}
