#include <GameWorld.h>
#include <Log.h>
#include <RNG.h>

struct DrawableComponent
{
    SDL_Texture *texture;
    SDL_Rect windowRect;
};

struct PositionComponent
{
    Vector2f position;
};

struct TransformComponent
{
    Vector2f velocity;
};

struct ColliderComponent
{
    Collider collider;
};

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

    m_character = std::make_unique<Character>(m_context, m_context->assetLoader->getAtlas("player"));

    // m_player = std::make_unique<Player>(m_context);
    // m_player->character()->tileMap(m_tileMap);

    // auto playerSpawner = m_tileMap->getObject<PlayerSpawnerObject>("PlayerSpawner");
    // m_player->character()->sprite().position(playerSpawner->position);

    // auto playerEntity = m_context->registry.create();
    // auto &sprite = m_context->registry.emplace<Sprite>(playerEntity);
    // sprite.texture(m_context->assetLoader->getTexture("player"));
    // m_context->registry.emplace<Vector2f>(playerEntity, Vector2f(15.f, 15.f));
    // m_context->registry.emplace<Collider>(playerEntity, Collider(32, 32));
    // m_context->registry.emplace<DrawableComponent>(playerEntity, m_context->assetLoader->getTexture("player"));
    // m_context->registry.emplace<PositionComponent>(playerEntity, Vector2f(10.0, 10.0));
    // m_context->registry.emplace<TransformComponent>(playerEntity, Vector2f(0.5, 0.5));
    // m_context->registry.emplace<ColliderComponent>(playerEntity, Collider(32, 32));
    m_camera = Camera(0, 0, 1280, 720);
}

void GameWorld::input(const SDL_Event &event)
{
    // m_player->input(event);
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

    auto view = m_context->registry.view<Sprite>();

    for (auto &e : view) {
        auto &sprite = view.get<Sprite>(e);
        sprite.draw(m_context->renderer);
    }

    // auto view = m_context->registry.view<DrawableComponent, PositionComponent>();

    // for (auto e : view) {
    //     auto &d = view.get<DrawableComponent>(e);
    //     auto &p = view.get<PositionComponent>(e);
    //     SDL_Rect textureRect = {0, 0, 32, 32};
    //     SDL_Rect windowRect = {(int)p.position.x, (int)p.position.y, 32, 32};
    //     m_context->renderer->draw(d.texture, &textureRect, &windowRect);
    // }

    if (m_debugDraw) {
        auto view = m_context->registry.view<Collider>();
        for (auto e : view) {
            auto &collider = view.get<Collider>(e);
            auto rect = collider.rect();
            m_context->renderer->drawRect(&rect);
        }
    }

    // m_context->renderer->camera(m_camera);
    // m_tileMap->draw(m_context->renderer);
    // m_player->draw();

    // m_camera.follow(m_player->character()->sprite().position());

    // if (m_debugDraw) {
    //     for (auto &[k, c] : m_tileMap->colliders()) {
    //         auto rect = c.rect();
    //         m_context->renderer->drawRect(&rect);
    //     }
    //     auto rect = m_player->character()->collider().rect();
    //     m_context->renderer->drawRect(&rect);
    // }

    // LOG_INFO(m_player->character()->sprite().position());
}

void GameWorld::update()
{
    if (m_context->assetLoader->loading()) {
        return;
    }

    {
        auto view = m_context->registry.view<Sprite, Vector2f>();

        for (auto &e : view) {
            auto &sprite = view.get<Sprite>(e);
            auto &transform = view.get<Vector2f>(e);
            sprite.position(transform);
        }
    }

    {
        auto view = m_context->registry.view<Collider, Vector2f>();

        for (auto &e : view) {
            auto &collider = view.get<Collider>(e);
            auto &transform = view.get<Vector2f>(e);
            collider.update(transform);
        }
    }

    m_character->update();

    // for (auto e : view) {
    //     auto &position = view.get<PositionComponent>(e);
    //     auto &transform = view.get<TransformComponent>(e);
    //     position.position.x += transform.velocity.x;
    //     position.position.y += transform.velocity.y;
    //     // // LOG_INFO(transform.position);
    // }

    // auto cview = m_context->registry.view<ColliderComponent, PositionComponent>();

    // for (auto e : view) {
    //     auto &colliderComponent = cview.get<ColliderComponent>(e);
    //     auto &positionComponent = cview.get<PositionComponent>(e);
    //     colliderComponent.collider.update(positionComponent.position);
    // }

    // m_player->update();
}