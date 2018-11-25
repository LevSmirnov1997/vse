#include "behaviours.hpp"

void seek(transform &t, vec2 dst)
{
	vec2 position = { t.transf.get_values()[3], t.transf.get_values()[7] };
	vec2 des_vel = dot(math::normalize(dst - position), t.max_speed);
	vec2 steering = des_vel - t.velocity;

	vec2 steer_force = math::truncate(steering, { t.max_speed, t.max_speed });
	vec2 accel{ steer_force.get_x() / t.mass, steer_force.get_y() / t.mass };

	t.velocity = math::truncate(t.velocity + accel, { t.max_speed, t.max_speed });
	t.transf = math::translate(t.transf, t.velocity);

	t.transf = math::rotate(t.transf, -t.angle);
	t.angle = math::degrees(std::atan2(t.velocity.get_y(), t.velocity.get_x())) + 90.f;
	t.transf = math::rotate(t.transf, t.angle);
}
