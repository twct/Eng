#include <Character.h>
#include <Log.h>

Character::Character(const CtxPtr &context, const Atlas &atlas) :
    m_context(context)
{
    moveSpeed(0.2);
    fallSpeed(0.05);

    m_fric = 1.1;
    m_direction = DIRECTION_NONE;

    m_sprite.texture(m_context->assetLoader->getTexture(atlas.textures.at(atlas.id).id));
    m_sprite.atlas(atlas);
    m_sprite.playAnimation(atlas.defaultAnimation);
}

void Character::direction(const Direction &direction)
{
    m_direction = direction;
}

void Character::moveSpeed(const double moveSpeed)
{
    m_moveSpeed = moveSpeed;
}

void Character::fallSpeed(const double fallSpeed)
{
    m_fallSpeed = fallSpeed;
}

Sprite &Character::sprite()
{
    return m_sprite;
}

void Character::draw()
{
    m_sprite.draw(m_context->renderer);
}

void Character::update()
{
    auto position = m_sprite.position();

    switch (m_direction) {
        case DIRECTION_LEFT:
            m_velocity.x -= m_moveSpeed;
            m_sprite.playAnimation("run");
            m_sprite.fliph();
        break;
        case DIRECTION_RIGHT:
            m_velocity.x += m_moveSpeed;
            m_sprite.playAnimation("run");
            m_sprite.flipn();
        break;
        case DIRECTION_NONE:
            m_sprite.playAnimation("idle");
        break;
    }


    m_velocity.x /= m_fric;
    m_velocity.y += m_fallSpeed;

    position.x += m_velocity.x;
    position.y += m_velocity.y;

    m_sprite.position(position);
}