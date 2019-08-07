#pragma once

#include "components/CTransform.hpp"

void seek(CTransform &t, vec2 dst);

void flee(CTransform &t, vec2 src);

void wander(CTransform &t);
