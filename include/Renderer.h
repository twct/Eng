#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <SDL2/SDL_render.h>
#include <Camera.h>

class Renderer
{
private:
    SDL_Renderer *m_renderer;
    bool m_paused;
    Camera m_camera;
public:
    Renderer(SDL_Window *window);
    ~Renderer();
    const bool active() const;
    SDL_Renderer *renderer();
    const unsigned int screenWidth() const;
    const unsigned int screenHeight() const;
    const float scaleX() const;
    const float scaleY() const;
    const Camera &camera() const;
    void camera(const Camera &camera);
    void scale(const float scaleX, const float scaleY);
    void clear(const SDL_Color &color = {0, 0, 155, 255});
    void present();
    void draw(SDL_Texture *texture, const SDL_Rect *textureRect, const SDL_Rect *windowRect);
    void draw(SDL_Texture *texture, const SDL_Rect *textureRect, const SDL_Rect *windowRect, const double angle, const SDL_Point *center, const SDL_RendererFlip flip);
};

#endif