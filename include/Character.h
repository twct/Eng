#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include <Collider.h>
#include <TileMap.h>
#include <Sprite.h>
#include <World.h>

enum class Direction
{
    None,
    Right,
    Left
};

class Character
{
private:
    CtxPtr m_context;
    Sprite m_sprite;
    Collider m_collider;
    Vector2f m_velocity;
    std::shared_ptr<TileMap> m_tileMap;
    double m_moveSpeed, m_fallSpeed, m_fric;
    Direction m_direction;
public:
    Character(const CtxPtr &context, const Atlas &atlas);
    void tileMap(const std::shared_ptr<TileMap> &tileMap);
    void direction(const Direction &direction);
    void moveSpeed(const double moveSpeed);
    void fallSpeed(const double fallSpeed);
    Sprite &sprite();
    const Collider &collider() const;
    void draw();
    void update();
};

#endif