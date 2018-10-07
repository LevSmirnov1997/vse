#pragma once
#include <vse/shader.hpp>
#include <vector>

class program
{
public:
	program();

	program(const program&) = delete;

	program(program &&temp);

	program& operator=(const program&) = delete;

	program& operator=(program &&temp);
	
	~program();

	void attach_shader(const shader& s) const;

	void detach_shader(const shader& s) const;

	bool link() const;

	void use() const;

	void unuse() const;

	bool valid() const;

	std::string info_log() const;

	using shader_args = std::pair<unsigned, const char *>;
	static program create_progarm(const std::vector<shader_args> &&args);

private:
	unsigned m_id;
};
