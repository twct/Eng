#ifndef __RNG_H__
#define __RNG_H__

#include <pcg_random.hpp>

class RNG
{
private:
    static pcg32 s_driver;
public:
    static void seed();
    static const int random(const int max);
};

#endif