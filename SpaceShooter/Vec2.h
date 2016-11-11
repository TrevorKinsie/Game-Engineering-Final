#ifndef VEC2_H_
#define VEC2_H_

struct Vec2
{
    float x, y;

    Vec2()
        : x(0.0f), y(0.0f)
    { }

    Vec2(float x, float y)
        : x(x), y(y)
    { }
};

float Distance(const Vec2& a, const Vec2& b);

float DistanceSquared(const Vec2& a, const Vec2& b);

#endif
