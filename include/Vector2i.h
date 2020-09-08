#ifndef __VECTOR2I_H__
#define __VECTOR2I_H__

#include <Vector2.h>

struct Vector2i : Vector2<int>
{
public:
    Vector2i();
    Vector2i(const int x, const int y);
};

#endif