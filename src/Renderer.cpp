#include <Renderer.h>

Renderer::Renderer(SDL_Window *window)
{
    m_paused = false;
    m_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(m_renderer);
}

const bool Renderer::active() const
{
    return m_renderer != nullptr;
}

SDL_Renderer *Renderer::renderer()
{
    return m_renderer;
}

void Renderer::camera(const Camera &camera)
{
    m_camera = camera;
}

void Renderer::scale(const float scaleX, const float scaleY)
{
    SDL_RenderSetScale(m_renderer, scaleX, scaleY);
}

void Renderer::clear(const SDL_Color &color)
{
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(m_renderer);
}

void Renderer::present()
{
    SDL_RenderPresent(m_renderer);
}

void Renderer::draw(SDL_Texture *texture, const SDL_Rect *textureRect, const SDL_Rect *windowRect)
{
    auto bounds = m_camera.bounds();

    SDL_Rect rect = {windowRect->x - bounds.x, windowRect->y - bounds.y, windowRect->w, windowRect->h};

    SDL_RenderCopy(m_renderer, texture, textureRect, &rect);
}

void Renderer::draw(SDL_Texture *texture, const SDL_Rect *textureRect, const SDL_Rect *windowRect, const double angle, const SDL_Point *center, const SDL_RendererFlip flip)
{
    auto bounds = m_camera.bounds();

    SDL_Rect rect = {windowRect->x - bounds.x, windowRect->h - bounds.h, windowRect->w, windowRect->h};

    SDL_RenderCopyEx(m_renderer, texture, textureRect, &rect, angle, center, flip);
}