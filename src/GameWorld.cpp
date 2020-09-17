#include <GameWorld.h>
#include <Log.h>

GameWorld::GameWorld(const std::shared_ptr<Application> &app) :
    World(app)
{
    m_context->assetLoader->addAtlas("player", "atlas/player.json");
    m_context->assetLoader->addTexture("tiles", "textures/tiles.png");
}

void GameWorld::init()
{
    LOG_INFO("GameWorld Init");

    m_player = std::make_unique<Player>(m_context);

    m_tileMap = std::make_unique<TileMap>(m_context->assetLoader->getTexture("tiles"), 32);
    m_tileMap->loadMap("levels/level.json");

    auto playerSpawner = m_tileMap->getObject<PlayerSpawnerObject>("PlayerSpawner");
    m_player->character()->sprite().position(playerSpawner->position);

    m_camera = Camera(0, 0, 1280, 720);
}

void GameWorld::input(const SDL_Event &event)
{
    m_player->input(event);
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

    m_context->renderer->camera(m_camera);
    m_tileMap->draw(m_context->renderer);
    m_player->draw();

    m_camera.follow(m_player->character()->sprite().position());
}

void GameWorld::update()
{
    if (m_context->assetLoader->loading()) {
        return;
    }

    m_player->update();
}