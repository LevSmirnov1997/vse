#pragma once
#include <al/gl/shapes.hpp>
#include <memory>

struct CModel
{
	std::unique_ptr<shape> ptr;
};
