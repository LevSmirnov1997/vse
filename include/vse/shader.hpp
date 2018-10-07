#pragma once
#include <string>

class shader
{
public:
	explicit shader(unsigned type);

	shader(unsigned type, const std::string &path);

	shader(const shader &) = delete;

	shader(shader &&temp);

	~shader();

	shader& operator=(const shader&) = delete;

	shader& operator=(shader &&temp);

	void set_source(const std::string & src) const;

	void load_source(const std::string & path) const;

	bool compile() const;

	bool valid() const;

	std::string info_log() const;

	unsigned id() const { return m_id;  }

	unsigned type() const { return m_type; }
private:
	unsigned m_id;
	unsigned m_type;
};
