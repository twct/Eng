#include <Clock.h>

Clock::Clock()
{
    reset();
}

void Clock::reset()
{
    m_base = SDL_GetTicks();
}

const Uint32 Clock::elapsed() const
{
    return SDL_GetTicks() - m_base;
}

const Uint32 Clock::elapsedAsSeconds() const
{
    return elapsed() / 1000;
}