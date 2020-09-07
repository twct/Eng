#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <Application.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include <RNG.h>
#include <Log.h>

#define MAX_FRAME_RATE 120
#define MIN_FRAME_RATE 30
#define UPDATE_INTERVAL (1.0 / MAX_FRAME_RATE)
#define MAX_CYCLES_PER_FRAME (MAX_FRAME_RATE / MIN_FRAME_RATE)

Application::Application()
{
    m_running = true;

    m_lastFrameTime = (double) SDL_GetTicks() / 1000.0;
    m_cyclesLeftOver = 0.0;
    m_currentTime = 0.0;
    m_updateIterations = 0.0;
}

const std::shared_ptr<Renderer> &Application::renderer()
{
    return m_renderer;
}

#ifdef __EMSCRIPTEN__
void Application::loopCallback(void *arg)
{
    static_cast<Application*>(arg)->loop();
}
#endif

void Application::loop()
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        // input
        switch (event.type) {
            case SDL_QUIT:
                m_running = false;
            break;
        }
    }

    m_currentTime = (double) SDL_GetTicks() / 1000.0;
    m_updateIterations = ((m_currentTime - m_lastFrameTime) + m_cyclesLeftOver);

    if (m_updateIterations > (MAX_CYCLES_PER_FRAME * UPDATE_INTERVAL)) {
        m_updateIterations = (MAX_CYCLES_PER_FRAME * UPDATE_INTERVAL);
    }

    while (m_updateIterations > UPDATE_INTERVAL) {
        m_updateIterations -= UPDATE_INTERVAL;
        // if (!m_worlds.empty()) {
        //     m_worlds.top()->update();
        // }
    }

    m_cyclesLeftOver = m_updateIterations;
    m_lastFrameTime = m_currentTime;
    // if (!m_worlds.empty()) {
        // m_worlds.top()->draw();
    // }
    // m_renderer->present();
    // SDL_RenderPresent(m_renderer);

    #ifdef __EMSCRIPTEN__
    if (!m_running) {
        emscripten_cancel_main_loop();
        shutdown();
    }
    #endif
}

void Application::shutdown()
{
    SDL_DestroyWindow(m_window);
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}

int Application::run(int argc, char **argv)
{
    RNG::seed();

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        LOG_ERROR("SDL_Init Error: " << SDL_GetError());
        return 1;
    }

    m_window = SDL_CreateWindow("Eng", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);

    if (!m_window) {
        LOG_ERROR("SDL_CreateWindow Error: " << SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_SetHintWithPriority(SDL_HINT_RENDER_SCALE_QUALITY, "0", SDL_HINT_OVERRIDE);
    m_renderer = std::make_shared<Renderer>(m_window);

    if (!m_renderer->active()) {
        SDL_DestroyWindow(m_window);
        LOG_ERROR("SDL_CreateRenderer Error: " << SDL_GetError());
        SDL_Quit();
        return 1;
    }

    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0) {
        LOG_ERROR("IMG_Init failed.");
        return 1;
    }

    if (TTF_Init() < 0) {
        LOG_ERROR("TTF_Init failed.");
        return 1;
    }

    int audio_rate = 22050;
    Uint16 audio_format = AUDIO_S16SYS;
    int audio_channels = 2;
    int audio_buffers = 4096;

    if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
        LOG_ERROR("SDL_Mixer init failed.");
        return 1;
    }

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(&Application::loopCallback, this, -1, 1);
#else
    while (m_running) {
        this->loop();
    }
    shutdown();
#endif

    return 0;
}