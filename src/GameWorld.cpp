#include <GameWorld.h>
#include <Log.h>

GameWorld::GameWorld(const std::shared_ptr<Application> &app) :
    World(app)
{
}

void GameWorld::init()
{
    LOG_INFO("GameWorld Init");
}

void GameWorld::input(const SDL_Event &event)
{

}

void GameWorld::draw()
{

}

void GameWorld::update()
{

}