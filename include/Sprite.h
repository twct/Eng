#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <SDL2/SDL_image.h>
#include <Drawable.h>

class Sprite : public Drawable
{
private:
    SDL_Texture *m_texture;
public:
    Sprite(SDL_Texture *texture);
};

#endif