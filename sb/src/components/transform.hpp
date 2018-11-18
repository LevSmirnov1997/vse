#pragma once
#include <al/math/mat4.hpp>
#include <al/math/mat_utils.hpp>
#include <cmath>
#include <iostream>

struct transform 
{
	mat4 transf;
    float angle = 0;
	vec2 velocity = { 1.f, 1.f };
	float max_speed = 10.f;
	float mass = 20.f;

	void seek(vec2 target)
	{
		vec2 position = { transf.get_values()[3], transf.get_values()[7] };
		vec2 des_vel = dot(math::normalize(target - position), max_speed);
		vec2 steering = des_vel - velocity;

		vec2 steer_force = math::truncate(steering, { max_speed, max_speed } );
		vec2 accel { steer_force.get_x() / mass, steer_force.get_y() / mass };

		velocity = math::truncate(velocity + accel, { max_speed, max_speed });
		transf = math::translate(transf, velocity);

		vec2 vel = velocity;
        transf = math::rotate(transf, -angle);
		angle = math::degrees(std::atan2(vel.get_y(), vel.get_x())) + 90.f;
        transf = math::rotate(transf, angle);
	}

    void move(float step)
    {
        float rad = math::radians(angle);
        float x = (step * sin(rad));
        float y = -fabs(step * cos(rad));
        if (cos(rad) < 0)
            y = -y;
        if (step < 0)
            y = -y;
        transf = math::translate(transf, vec2(x, y));
    }

    void rotate(float degr)
    {
        angle += degr;
        transf = math::rotate(transf, degr);
    }
};
