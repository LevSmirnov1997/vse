#pragma once
#include <al/ecs.hpp>
#include <components/CCollision.hpp>

class CollisionDetectionSystem: public System
{
public:
    void update(ecs &e);
};
