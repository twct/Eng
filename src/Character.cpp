#include <Character.h>
#include <Log.h>

Character::Character(const CtxPtr &context, const Atlas &atlas) :
    m_context(context)
{
    moveSpeed(0.2);
    fallSpeed(0.05);

    m_fric = 1.1;
    m_direction = Direction::None;

    auto atlasTexture = atlas.textures.at(atlas.id);

    m_sprite.texture(m_context->assetLoader->getTexture(atlasTexture.id));
    m_sprite.atlas(atlas);
    m_sprite.playAnimation(atlas.defaultAnimation);

    m_collider = Collider(32, 32);
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

void Character::tileMap(const std::shared_ptr<TileMap> &tileMap)
{
    m_tileMap = tileMap;
}

Sprite &Character::sprite()
{
    return m_sprite;
}

const Collider &Character::collider() const
{
    return m_collider;
}

void Character::draw()
{
    m_sprite.draw(m_context->renderer);
}

void Character::update()
{
    auto position = m_sprite.position();

    switch (m_direction) {
        case Direction::Left:
            m_velocity.x -= m_moveSpeed;
            m_sprite.playAnimation("run");
            m_sprite.fliph();
        break;
        case Direction::Right:
            m_velocity.x += m_moveSpeed;
            m_sprite.playAnimation("run");
            m_sprite.flipn();
        break;
        case Direction::None:
            m_sprite.playAnimation("idle");
        break;
    }


    m_velocity.x /= m_fric;
    m_velocity.y += m_fallSpeed;

    position.x += m_velocity.x;
    position.y += m_velocity.y;

    auto colliders = m_tileMap->nearbyColliders(m_collider);

    for (auto &collider : colliders) {
        auto me = m_collider.rect();
        auto surface = collider.rect();
        auto result = m_collider.intersectsResult(collider);
        // Horizontal collision
        if (result.h < result.w) {

        }
        // Vertical collision
        else {
            // Floor collision
            if (me.y + me.h < surface.y + surface.y) {
                if (m_velocity.y > 0) {
                    position.y -= result.h;
                    m_velocity.y = 0.0;
                }
            }
            // Ceiling collision
            else {

            }
        }
    }

    m_sprite.position(position);
    m_collider.update(position, {0, 9});
}