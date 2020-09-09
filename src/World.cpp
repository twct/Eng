#include <Application.h>
#include <World.h>

World::World(const std::shared_ptr<Application> &app)
{
    m_context = std::make_shared<Context>();

    m_context->app = app;
    m_context->renderer = m_context->app->renderer();
    m_context->assetLoader = std::make_shared<AssetLoader>(m_context->renderer);
}