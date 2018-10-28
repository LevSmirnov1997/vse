#pragma once
#include <al/gl/shapes.hpp>
#include <memory>

struct model
{
	std::unique_ptr<shape> ptr;
};
