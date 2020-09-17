#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <SDL2/SDL_events.h>
#include <Character.h>
#include <TileMap.h>
#include <World.h>

class Player
{
private:
    CtxPtr m_context;
    std::shared_ptr<Character> m_character;
    std::shared_ptr<TileMap> m_tileMap;
    bool m_right, m_left;
public:
    Player(CtxPtr context);
    const std::shared_ptr<Character> &character();
    void input(const SDL_Event &event);
    void draw();
    void update();
};

#endif