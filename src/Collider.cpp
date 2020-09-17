#include <Collider.h>

Collider::Collider() :
    Collider(0, 0)
{
}

Collider::Collider(const Collider &c) :
    m_rect(c.rect())
{
}

Collider::Collider(const int width, const int height)
{
    m_rect = {0, 0, width, height};
}

const SDL_Rect &Collider::rect() const
{
    return m_rect;
}

const bool Collider::intersects(const Collider &c) const
{
    auto rect = c.rect();

    return SDL_HasIntersection(&m_rect, &rect);
}

const SDL_Rect Collider::intersectsResult(const Collider &c) const
{
    SDL_Rect result;
    auto rect = c.rect();

    SDL_IntersectRect(&m_rect, &rect, &result);

    return result;
}

void Collider::update(const Vector2f &position, const SDL_Point &origin)
{
    m_rect.x = (int) position.x;
    m_rect.y = (int) position.y;
}