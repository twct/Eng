#include <GameWorld.h>
#include <Log.h>

GameWorld::GameWorld(const std::shared_ptr<Application> &app) :
    World(app)
{
    m_debugDraw = false;

    m_context->assetLoader->addAtlas("player", "atlas/player.json");
    m_context->assetLoader->addTexture("tiles", "textures/tiles.png");
}

void GameWorld::init()
{
    LOG_INFO("GameWorld Init");

    m_tileMap = std::make_shared<TileMap>(m_context->assetLoader->getTexture("tiles"), 32);
    m_tileMap->loadMap("levels/level.json");

    m_player = std::make_unique<Player>(m_context);
    m_player->character()->tileMap(m_tileMap);

    auto playerSpawner = m_tileMap->getObject<PlayerSpawnerObject>("PlayerSpawner");
    m_player->character()->sprite().position(playerSpawner->position);

    m_camera = Camera(0, 0, 1280, 720);
}

void GameWorld::input(const SDL_Event &event)
{
    m_player->input(event);
    switch (event.type) {
        case SDL_KEYUP:
            switch (event.key.keysym.sym) {
                case SDLK_F3:
                    m_debugDraw = !m_debugDraw;
                    LOG_INFO("Debug Draw: " << (m_debugDraw ? "On" : "Off"));
                break;
            }
        break;
    }
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

    if (m_debugDraw) {
        for (auto &[k, c] : m_tileMap->colliders()) {
            auto rect = c.rect();
            m_context->renderer->drawRect(&rect);
        }
        auto rect = m_player->character()->collider().rect();
        m_context->renderer->drawRect(&rect);
    }

    // LOG_INFO(m_player->character()->sprite().position());
}

void GameWorld::update()
{
    if (m_context->assetLoader->loading()) {
        return;
    }

    m_player->update();
}