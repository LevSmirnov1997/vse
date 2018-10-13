#include "shader.hpp"
#include <glad/glad.h>
#include <fstream>
#include <cerrno>

shader::shader(unsigned type)
	: m_id(glCreateShader(type)),
	  m_type(type)
{
}

shader::shader(unsigned type, const std::string &path)
	: m_id(glCreateShader(type)),
	  m_type(type)
{
	this->load_source(path);
	if (!this->compile())
		throw std::runtime_error(this->info_log());
}

shader::shader(shader &&temp)
	: m_id(temp.m_id),
	  m_type(temp.m_type)
{
	temp.m_id = ~0u;
}

shader& shader::operator=(shader &&temp)
{
	this->m_id = temp.m_id;
	this->m_type = temp.m_type;
	temp.m_id = ~0u;
	return *this;
}

shader::~shader()
{
	if (this->valid())
		glDeleteShader(m_id);
}

bool shader::compile() const
{
	glCompileShader(m_id);
	GLint success;
	glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);
	return success && this->valid();
}

void shader::set_source(const std::string &src) const
{
	auto source = src.c_str();
	glShaderSource(m_id, 1, &source, nullptr);
}

void shader::load_source(const std::string &path) const
{
	std::ifstream is(path);
	if (!is) {
		 auto err = std::string("Invalid shader source file: " + path + '\n' + std::strerror(errno));
		 throw std::runtime_error(err.c_str());
	}
	this->set_source(std::string(std::istreambuf_iterator<char>(is), std::istreambuf_iterator<char>()));
}

bool shader::valid() const
{
	return glIsShader(m_id);
}

std::string shader::info_log() const
{
	GLint size = 0;
	glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &size);
	if (0 == size)
		return "";

	std::string info;
	info.resize(size);
	glGetShaderInfoLog(m_id, size, nullptr, &info[0]);
	return info;
}
