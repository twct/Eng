#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <SDL2/SDL_image.h>
#include <AtlasReader.h>
#include <Drawable.h>
#include <Clock.h>

class Renderer;

class Sprite : public Drawable
{
private:
    Atlas m_atlas;
    SDL_Texture *m_texture;
    SDL_Point m_center;
    SDL_Rect m_textureRect, m_windowRect;
    Uint32 m_currentFrame;
    Clock m_animationClock;
    unsigned int m_animationSpeed;
    bool m_isAnimating, m_loopAnimation;
    AtlasAnimation m_currentAnimation;
public:
    Sprite();
    void texture(SDL_Texture *texture);
    void atlas(const Atlas &atlas);
    void animationSpeed(const unsigned int animationSpeed);
    void playAnimation(const std::string &animation, bool loop = true);
    void center(const int x, const int y);
    const SDL_Point &center() const;
    void draw(const std::shared_ptr<Renderer> &renderer) override;
};

#endif