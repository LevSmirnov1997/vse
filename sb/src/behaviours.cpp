#include "behaviours.hpp"
#include <al/math.hpp>
#include <random>
//#include <iostream>

static void update(transform &t, vec2 steering)
{
	vec2 steer_force = math::truncate(steering, { t.max_speed, t.max_speed });
	vec2 accel{ steer_force.get_x() / t.mass, steer_force.get_y() / t.mass };

	// unproportional truncation of the axises
	t.velocity = math::truncate(t.velocity + accel, { t.max_speed, t.max_speed });
	t.transf = math::translate(t.transf, t.velocity);

	t.transf = math::rotate(t.transf, -t.angle);
	t.angle = math::degrees(std::atan2(t.velocity.get_y(), t.velocity.get_x())) + 90.f;
	t.transf = math::rotate(t.transf, t.angle);
//	std::cout << "v: " << t.velocity.get_x() << " " << t.velocity.get_y() << std::endl; 
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
	static std::random_device rd;
	static std::mt19937 rng(rd());
	return rng;
}

static vec2 vec_rotate(const vec2 &v, float angle_deg)
{
	return {
		std::cos(math::radians(angle_deg)) * v.magn(),
		std::sin(math::radians(angle_deg)) * v.magn()
	};
}

void wander(transform &t)
{
	const float circle_distance = 5.f;
	const float circle_radius = 35.f;
	vec2 circle_pos = t.velocity;
	circle_pos = math::normalize(circle_pos);
	circle_pos = dot(circle_pos, circle_distance);

	// calculate pseudo-random number
	float max_angle_speed = 5.f;
	std::uniform_real_distribution<> dist_angle(0.f, max_angle_speed);
	std::uniform_int_distribution<> one_of_hundred(0, 99);
	static float rand_value = 0.f;
	static float sign = (dist_angle(get_rng()) >= max_angle_speed/2.f) ? 1.f : -1.f;
	int chance = one_of_hundred(get_rng());
	if (chance > 89)
		sign = -sign;
	rand_value += sign * dist_angle(get_rng());

	vec2 displacement = { 0.f, -1.f };
	displacement = dot(displacement, circle_radius);
	displacement = vec_rotate(displacement, rand_value);

	vec2 wander_force = displacement + circle_pos;
	update(t, wander_force);
}

