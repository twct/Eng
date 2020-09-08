#ifndef __VECTOR2F_H__
#define __VECTOR2F_H__

#include <Vector2.h>

struct Vector2f : Vector2<float>
{
    Vector2f();
    Vector2f(float x, float y);

    static float distance(const Vector2f &a, const Vector2f &b);
    void normalize();
    const Vector2f normalized();
    const Vector2f lerp(const Vector2f &b, double t);
};

#endif