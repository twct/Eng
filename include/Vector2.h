#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <cmath>

template <typename T>
struct Vector2
{
    T x, y;

    Vector2(T x, T y)
    {
        this->x = x;
        this->y = y;
    }

    static float distance(const Vector2<T> &a, const Vector2<T> &b)
    {
        return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) * 1.0);
    }

    Vector2<T> operator+(const Vector2<T> &v)
    {
        Vector2<T> vector;
        vector.x = this->x + v.x;
        vector.y = this->y + v.y;

        return vector;
    }

    Vector2<T> operator-(const Vector2<T> &v)
    {
        Vector2<T> vector;
        vector.x = this->x - v.x;
        vector.y = this->y - v.y;

        return vector;
    }

    Vector2<T> operator*(const Vector2<T> &v)
    {
        Vector2<T> vector;
        vector.x = this->x * v.x;
        vector.y = this->y * v.y;

        return vector;
    }

    Vector2<T> operator/(const Vector2<T> &v)
    {
        Vector2<T> vector;
        vector.x = this->x / v.x;
        vector.y = this->y / v.y;

        return vector;
    }
};

#endif