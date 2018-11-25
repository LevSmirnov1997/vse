#include "behaviours.hpp"
#include <al/math.hpp>
#include <iostream>
#include <random>

static void update(transform &t, vec2 steering)
{
	vec2 steer_force = math::truncate(steering, { t.max_speed, t.max_speed });
	vec2 accel{ steer_force.get_x() / t.mass, steer_force.get_y() / t.mass };

	t.velocity = math::truncate(t.velocity + accel, { t.max_speed, t.max_speed });
	t.transf = math::translate(t.transf, t.velocity);

	t.transf = math::rotate(t.transf, -t.angle);
	t.angle = math::degrees(std::atan2(t.velocity.get_y(), t.velocity.get_x())) + 90.f;
	t.transf = math::rotate(t.transf, t.angle);
}

void seek(transform &t, vec2 dst)
{
	vec2 position = { t.transf.get_values()[3], t.transf.get_values()[7] };
	vec2 des_vel = dot(math::normalize(dst - position), t.max_speed);
	vec2 steering = des_vel - t.velocity;
	update(t, steering);
}

void flee(transform &t, vec2 src)
{
	vec2 position = { t.transf.get_values()[3], t.transf.get_values()[7] };
	vec2 des_vel = dot(math::normalize(position - src), t.max_speed);
	vec2 steering = des_vel - t.velocity;
	update(t, steering);
}

static std::mt19937 &get_rng()
{
	static std::mt19937 rng;
	static bool init = false;
	if (init)
		return rng;
	rng.seed(std::random_device()());
	init = true;
}

void wander(transform &t)
{
	vec2 actor_pos = { t.transf.get_values()[3], t.transf.get_values()[7] };

	float step = 100.f;
	float rad = math::radians(t.angle);
	std::cout << rad << std::endl;
	float x = (step * sin(rad));
	float y = -fabs(step * cos(rad));
	if (cos(rad) < 0)
		y = -y;
	if (step < 0)
		y = -y;
	vec2 sphere_pos = { actor_pos.get_x() + x, actor_pos.get_y() + y };

	float max_angle = 5.f;
	std::uniform_real_distribution<> dist_angle(-max_angle, max_angle);
	mat4 rotation;
	rotation = math::rotate(rotation, dist_angle(get_rng()), sphere_pos);

	const float radius = 30.f;
	vec2 cp{ x, y };
	cp = dot(math::normalize(cp), radius);
	cp += sphere_pos;
	float deviation = dist_angle(get_rng());
	float a = radius * std::sin(math::radians(deviation));
	float b = a / std::tan(math::radians((180.f - deviation) / 2.f));
	t.velocity = { t.velocity.get_x() - b, t.velocity.get_y() - a };
	t.angle += deviation;
	// t.transf = math::rotate(t.transf, t.angle);

	seek(t, cp);
}
