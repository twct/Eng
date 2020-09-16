#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include <Sprite.h>
#include <World.h>

class Character
{
private:
    CtxPtr m_context;
    Sprite m_sprite;
public:
    Character(const CtxPtr &context, const Atlas &atlas);
    Sprite &sprite();
};

#endif