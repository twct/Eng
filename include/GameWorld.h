#ifndef __GAMEWORLD_H__
#define __GAMEWORLD_H__

#include <World.h>

class GameWorld : public World
{
public:
    GameWorld(const std::shared_ptr<Application> &app);
    void init() override;
    void draw() override;
    void input(const SDL_Event &event) override;
    void update() override;
};

#endif