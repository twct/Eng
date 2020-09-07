#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <SDL2/SDL_render.h>

class Renderer
{
private:
    SDL_Renderer *m_renderer;
    bool m_paused;
public:
    Renderer(SDL_Window *window);
    ~Renderer();
    const bool active() const;
    void scale(const float scaleX, const float scaleY);
    void clear(const SDL_Color &color = {0, 0, 155, 255});
    void present();
};

#endif