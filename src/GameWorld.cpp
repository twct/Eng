#include <GameWorld.h>
#include <Log.h>

GameWorld::GameWorld(const std::shared_ptr<Application> &app) :
    World(app)
{
    // m_context->assetLoader->addTexture("player", "textures/player.png");
    m_context->assetLoader->addAtlas("player", "atlas/player.json");
}

void GameWorld::init()
{
    LOG_INFO("GameWorld Init");

    m_character = std::make_unique<Character>(m_context, m_context->assetLoader->getAtlas("player"));

    // m_sprite.texture(m_context->assetLoader->getTexture("player"));
    // m_sprite.position({100, 100});
}

void GameWorld::input(const SDL_Event &event)
{

}

void GameWorld::draw()
{
    if (m_context->assetLoader->loading()) {
        World::drawLoadingScene();
        m_context->assetLoader->load(
            std::bind(&GameWorld::init, this)
        );
        return;
    }

    m_character->sprite().draw(m_context->renderer);

    // m_sprite.draw(m_context->renderer);
}

void GameWorld::update()
{

}