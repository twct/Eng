#include <Character.h>

Character::Character(const CtxPtr &context, const Atlas &atlas) :
    m_context(context)
{
    m_sprite.texture(m_context->assetLoader->getTexture(atlas.textures.at(atlas.id).id));
    m_sprite.atlas(atlas);
    m_sprite.playAnimation(atlas.defaultAnimation);
}

Sprite &Character::sprite()
{
    return m_sprite;
}