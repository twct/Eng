#include <random>
#include <RNG.h>

pcg32 RNG::s_driver;

void RNG::seed()
{
    pcg_extras::seed_seq_from<std::random_device> source;
    s_driver = pcg32(source);
}

const int RNG::random(const int max)
{
    return s_driver(max);
}