#pragma once

#include "components/transform.hpp"

void seek(transform &t, vec2 dst);

void flee(transform &t, vec2 src);

void wander(transform &t);
