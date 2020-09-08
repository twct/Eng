#include <Vector2f.h>
#include <math.h>

Vector2f::Vector2f() :
    Vector2<float>(0.0, 0.0)
{
}

Vector2f::Vector2f(float x, float y) :
    Vector2<float>(x, y)
{
}

const Vector2f Vector2f::lerp(const Vector2f &b, double t)
{
    Vector2f vector = Vector2f(this->x, this->y);

    vector.x = (1 - t) * this->x + t * b.x;
    vector.y = (1 - t) * this->y + t * b.y;

    return vector;
}

void Vector2f::normalize()
{
    float m = 1.0f / sqrt(this->x * this->x + this->y * this->y);

    this->x *= m;
    this->y *= m;
}

const Vector2f Vector2f::normalized()
{
    Vector2f vector = Vector2f(this->x, this->y);
    vector.normalize();

    return vector;
}