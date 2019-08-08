#include "CollisionDetectionSystem.hpp"
#include <components/CTransform.hpp>
#include <components/CModel.hpp>
#include <al/gl/shapes.hpp>
#include <al/math.hpp>

using shape_type = shape::shape_type;

static bool is_colliding(const std::vector<vec2> &v, shape_type type);
static std::vector<vec2> local_to_world(const mat4 &t, shape_type type);
static std::vector<vec2> translate_to_coords(const std::vector<vec2> &v, const mat4 &t);
static auto form_line_equation(vec2 x, vec2 y);

void CollisionDetectionSystem::update(ecs &e)
{
    // TODO: optimize the algorithm
    const auto ents = e.with<CModel, CTransform, CCollision>();

    for (unsigned i = 0; i < ents.size() - 1; ++i)
    {
        const auto left_type = ents[i].get<CModel>().ptr->type();
        const mat4 &left_transform = ents[i].get<CTransform>().transf;
        // try to calculate inverse matrix of the left entity
        mat4 inv;
        bool inversed = math::inverse(left_transform, inv);

        for (auto j = i + 1; j < ents.size(); ++j)
        {
            const auto right_type = ents[j].get<CModel>().ptr->type();
            const mat4 &right_transform = ents[j].get<CTransform>().transf;

            // if left's matrix is not inversed
            if (! inversed)
            {
                // try to calculate inverse matrix of the right entity
                if(! math::inverse(right_transform, inv))
                {
                    // if none of the transforms are inversable do the expensive collision check
                    // TODO: add logging
                    // TODO: implement collision check in world coordinates
                    continue;
                }
            }

            const auto &tr = inversed ? left_transform : right_transform;
            const auto ty = inversed ? left_type : right_type;
            // move entity to world coordinates
            auto v = local_to_world(tr, ty);
            // move entity to the local coordinates of the other entity
            v = translate_to_coords(v, inv);
            // check for collision
        }
    }
}

static const std::vector<vec2> RV = {
    { RectangleVerticies[0], RectangleVerticies[1] },
    { RectangleVerticies[2], RectangleVerticies[3] },
    { RectangleVerticies[4], RectangleVerticies[5] },
    { RectangleVerticies[6], RectangleVerticies[7] }
};

static const std::vector<vec2> TV = {
    { TriangleVerticies[0], TriangleVerticies[1] },
    { TriangleVerticies[2], TriangleVerticies[3] },
    { TriangleVerticies[4], TriangleVerticies[5] }
};

static std::vector<vec2> local_to_world(const mat4 &t, shape_type type)
{
    const auto &initial = type == shape_type::triangle ? TV : RV;
    return translate_to_coords(initial, t);
}

static std::vector<vec2> translate_to_coords(const std::vector<vec2> &v, const mat4 &t)
{
    std::vector<vec2> r;
    for (unsigned i = 0; i < v.size(); ++i)
    {
        r.push_back(math::mult(t, v[i]));
    }
    return r;
}

static auto form_line_equation(vec2 x, vec2 y)
{
    float a = y.y - x.y;
    float b = x.x - y.x;
    float c = a*x.x + b*x.y;
    return [a,b,c](vec2 p) { return c == (a*p.x + b*p.y); };
}

static bool is_colliding(const std::vector<vec2> &x, shape_type type)
{
    // TODO: rewrite with use of actuall values instead of 50s
    const auto &y = type == shape_type::triangle ? TV : RV;

    // check if vertices match
    for (auto px : x)
    {
        for (auto py : y)
        {
            if (px == py)
                return true;
        }
    }

    //check if on edges
    if (type == shape_type::rectangle)
    {
        for (auto p : x)
        {
            if ((p.y == 50  && (p.x >= -50 && p.x <= 50)) || // top
                (p.y == -50 && (p.x >= -50 && p.x <= 50)) || // bottom
                (p.x == 50  && (p.y >= -50 && p.y <= 50)) || // right
                (p.x == -50 && (p.y >= -50 && p.y <= 50)))   // left
            {
                return true;
            }
        }
    }
    else
    {
        for (auto p : x)
        {
            // try solve the edges' equations

            static const auto left_eq = form_line_equation({-50, -50}, {0, 50});
            static const auto right_eq = form_line_equation({50, -50}, {0, 50});

            // bottom
            if ((p.y == -50 && (p.x >= -50 && p.x <= 50)))
            {
                return true;
            }

            // left or right
            if ((p.y >= -50 && p.y <= 50))
            {
                if(((p.x >= -50 && p.x <= 0) && left_eq(p)) ||
                   ((p.x >= 0 && p.x <= 50) && right_eq(p)))
                {
                    return true;
                }
            }
        }
    }
    // TODO: form lines from point to all vertices and check for intersections

    return false;
}
