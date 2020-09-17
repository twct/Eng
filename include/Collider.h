#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include <SDL2/SDL_rect.h>
#include <Vector2f.h>

class Collider
{
private:
    SDL_Rect m_rect;
public:
    Collider();
    Collider(const int width, const int height);
    Collider(const Collider &c);
    const SDL_Rect &rect() const;
    const bool intersects(const Collider &c) const;
    const SDL_Rect intersectsResult(const Collider &c) const;
    void update(const Vector2f &position, const SDL_Point &origin = {0, 0});
};

#endif