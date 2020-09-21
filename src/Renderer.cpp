#include <Renderer.h>
#include <Log.h>

Renderer::Renderer(SDL_Window *window)
{
    m_paused = false;
    m_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(m_renderer);
}

const bool Renderer::active() const
{
    return m_renderer != nullptr;
}

const unsigned int Renderer::screenWidth() const
{
    int width;
    SDL_GetRendererOutputSize(m_renderer, &width, nullptr);

    return width / (int) scaleX();
}

const unsigned int Renderer::screenHeight() const
{
    int height;
    SDL_GetRendererOutputSize(m_renderer, nullptr, &height);

    return height / (int) scaleY();
}

const float Renderer::scaleX() const
{
    float scaleX;
    SDL_RenderGetScale(m_renderer, &scaleX, nullptr);

    return scaleX;
}

const float Renderer::scaleY() const
{
    float scaleY;
    SDL_RenderGetScale(m_renderer, nullptr, &scaleY);

    return scaleY;
}

SDL_Renderer *Renderer::renderer()
{
    return m_renderer;
}

void Renderer::camera(const Camera &camera)
{
    m_camera = camera;
}

const Camera &Renderer::camera() const
{
    return m_camera;
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

void Renderer::drawRect(SDL_Rect *rect, const SDL_Color &color)
{
    auto bounds = m_camera.bounds();

    SDL_Rect object = {rect->x - bounds.x, rect->y - bounds.y, rect->w, rect->h};

    SDL_Color old;
    SDL_GetRenderDrawColor(m_renderer, &old.r, &old.g, &old.b, &old.a);
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(m_renderer, &object);
    SDL_SetRenderDrawColor(m_renderer, old.r, old.g, old.b, old.a);
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

    SDL_Rect rect = {windowRect->x - bounds.x, windowRect->y - bounds.y, windowRect->w, windowRect->h};

    SDL_RenderCopyEx(m_renderer, texture, textureRect, &rect, angle, center, flip);
}