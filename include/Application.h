#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <SDL2/SDL.h>
#include <Renderer.h>
#include <memory>

class Application
{
private:
    bool m_running;
    double m_lastFrameTime;
    double m_cyclesLeftOver;
    double m_updateIterations;
    double m_currentTime;
    SDL_Window *m_window;
    std::shared_ptr<Renderer> m_renderer;
    void shutdown();
public:
    Application();
    void loop();
    #ifdef __EMSCRIPTEN__
    static void loopCallback(void *arg);
    #endif
    const std::shared_ptr<Renderer> &renderer();
    int run(int argc, char **argv);
};

#endif

