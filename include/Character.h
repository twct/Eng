#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include <Sprite.h>
#include <World.h>

enum Direction
{
    DIRECTION_NONE,
    DIRECTION_RIGHT,
    DIRECTION_LEFT
};

class Character
{
private:
    CtxPtr m_context;
    Sprite m_sprite;
    Vector2f m_velocity;
    double m_moveSpeed, m_fallSpeed, m_fric;
    Direction m_direction;
public:
    Character(const CtxPtr &context, const Atlas &atlas);
    void direction(const Direction &direction);
    void moveSpeed(const double moveSpeed);
    void fallSpeed(const double fallSpeed);
    Sprite &sprite();
    void draw();
    void update();
};

#endif