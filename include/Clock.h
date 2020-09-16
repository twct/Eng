#ifndef __CLOCK_H__
#define __CLOCK_H__

#include <SDL2/SDL_timer.h>

class Clock
{
private:
    Uint32 m_base;
public:
    Clock();
    void reset();
    const Uint32 elapsed() const;
    const Uint32 elapsedAsSeconds() const;
};

#endif