#ifndef __WORLD_H__
#define __WORLD_H__

#include <Application.h>

class World
{
private:
    std::shared_ptr<Application> m_app;
public:
    World(const std::shared_ptr<Application> &app);
};

#endif