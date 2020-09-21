#ifndef __WORLD_H__
#define __WORLD_H__

#include <entt/entity/registry.hpp>
#include <AssetLoader.h>
#include <memory>

class Application;

struct Context
{
    std::shared_ptr<Application> app;
    std::shared_ptr<AssetLoader> assetLoader;
    std::shared_ptr<Renderer> renderer;
    entt::registry registry;
};

typedef std::shared_ptr<Context> CtxPtr;

class World
{
protected:
    CtxPtr m_context;
public:
    World(const std::shared_ptr<Application> &app);
    void drawLoadingBar(int x, int y, int w, int h, float percent, const SDL_Color &fgColor, const SDL_Color &bgColor);
    void drawLoadingScene();
    virtual void init() = 0;
    virtual void draw() = 0;
    virtual void input(const SDL_Event &event) = 0;
    virtual void update() = 0;
};

#endif