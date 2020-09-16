#ifndef __DRAWABLE_H__
#define __DRAWABLE_H__

#include <SDL2/SDL_render.h>
#include <Vector2f.h>
#include <memory>

class Renderer;

class Drawable
{
protected:
    Vector2f m_position;
    double m_angle, m_opacity;
    SDL_RendererFlip m_flip;
public:
    Drawable();
    const Vector2f &position() const;
    const double angle() const;
    const double opacity() const;
    const SDL_RendererFlip flip() const;
    void position(const Vector2f &position);
    void angle(const double angle);
    void opacity(const double opacity);
    void flip(const SDL_RendererFlip flip);
    virtual void draw(const std::shared_ptr<Renderer> &renderer) = 0;
};

#endif