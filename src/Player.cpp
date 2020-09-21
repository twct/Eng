#include <Player.h>

// Player::Player(CtxPtr context) :
//     m_context(context)
// {
//     m_right = false;
//     m_left = false;

//     m_character = std::make_unique<Character>(m_context, m_context->assetLoader->getAtlas("player"));
// }

// const std::shared_ptr<Character> &Player::character()
// {
//     return m_character;
// }

// void Player::input(const SDL_Event &event)
// {
//     switch (event.type) {
//         case SDL_KEYDOWN:
//             switch (event.key.keysym.sym) {
//                 case SDLK_LEFT:
//                     m_left = true;
//                 break;
//                 case SDLK_RIGHT:
//                     m_right = true;
//                 break;
//             }
//         break;
//         case SDL_KEYUP:
//             switch (event.key.keysym.sym) {
//                 case SDLK_LEFT:
//                     m_left = false;
//                 break;
//                 case SDLK_RIGHT:
//                     m_right = false;
//                 break;
//             }
//         break;
//     }
// }

// void Player::draw()
// {
//     m_character->draw();
// }

// void Player::update()
// {
//     if (m_left && !m_right) {
//         m_character->direction(DIRECTION_LEFT);
//     }
    
//     if (!m_left && m_right) {
//         m_character->direction(DIRECTION_RIGHT);
//     }

//     if (!m_left && !m_right) {
//         m_character->direction(DIRECTION_NONE);
//     }

//     m_character->update();
// }