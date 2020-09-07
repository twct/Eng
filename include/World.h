#ifndef __WORLD_H__
#define __WORLD_H__

#include <AssetLoader.h>
#include <memory>

class Application;

struct Context
{
    std::shared_ptr<AssetLoader> assetLoader;
    std::shared_ptr<Renderer> renderer;
};

class World
{
private:
    std::shared_ptr<Application> m_app;
public:
    World(const std::shared_ptr<Application> &app);
    virtual void draw() = 0;
    virtual void input(const SDL_Event &event) = 0;
    virtual void update() = 0;
};

#endif