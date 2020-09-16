#ifndef __GAMEWORLD_H__
#define __GAMEWORLD_H__

#include <Character.h>
#include <World.h>

class GameWorld : public World
{
private:
    std::unique_ptr<Character> m_character;
public:
    GameWorld(const std::shared_ptr<Application> &app);
    void init() override;
    void draw() override;
    void input(const SDL_Event &event) override;
    void update() override;
};

#endif