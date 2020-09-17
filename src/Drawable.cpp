#include <Drawable.h>

Drawable::Drawable()
{
    m_angle = 0.0;
    m_opacity = 1.0;
    m_flip = SDL_FLIP_NONE;
}
const Vector2f &Drawable::position() const
{
    return m_position;
}

const double Drawable::angle() const
{
    return m_angle;
}

const double Drawable::opacity() const
{
    return m_opacity;
}

const SDL_RendererFlip Drawable::flip() const
{
    return m_flip;
}

void Drawable::position(const Vector2f &position)
{
    m_position = position;
}

void Drawable::angle(const double angle)
{
    m_angle = angle;
}

void Drawable::opacity(const double opacity)
{
    m_opacity = opacity;
}

void Drawable::flip(const SDL_RendererFlip flip)
{
    m_flip = flip;
}

void Drawable::flipn()
{
    flip(SDL_FLIP_NONE);
}

void Drawable::fliph()
{
    flip(SDL_FLIP_HORIZONTAL);
}

void Drawable::flipv()
{
    flip(SDL_FLIP_VERTICAL);
}