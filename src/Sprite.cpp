#include <Renderer.h>
#include <Sprite.h>
#include <Log.h>

using namespace std::string_literals;

Sprite::Sprite() :
    Drawable()
{
    m_textureRect = {0, 0, 0, 0};
    m_windowRect = {0, 0, 0, 0};

    m_animationSpeed = 100;
    m_isAnimating = false;
    m_loopAnimation = false;

    center(0, 0);
}

void Sprite::texture(SDL_Texture *texture)
{
    m_texture = texture;

    int w, h;
    SDL_QueryTexture(m_texture, nullptr, nullptr, &w, &h);

    m_textureRect.w = w;
    m_textureRect.h = h;

    m_windowRect.w = w;
    m_windowRect.h = h;

    center(w / 2, h / 2);
}

void Sprite::atlas(const Atlas &atlas)
{
    m_atlas = atlas;
}

void Sprite::animationSpeed(const unsigned int animationSpeed)
{
    m_animationSpeed = animationSpeed;
}

void Sprite::playAnimation(const std::string &animation, bool loop)
{
    auto animationIter = m_atlas.animations.find(animation);

    if (animationIter == m_atlas.animations.end()) {
        throw std::runtime_error("Unable to play animation: "s + animation);
    }

    m_currentAnimation = animationIter->second;
    auto atlasTexture = m_atlas.textures.at(m_currentAnimation.texture_id);

    m_textureRect.w = atlasTexture.w;
    m_textureRect.h = atlasTexture.h;

    m_windowRect.w = atlasTexture.w;
    m_windowRect.h = atlasTexture.h;

    m_isAnimating = true;
    m_loopAnimation = true;

    center(atlasTexture.w / 2, atlasTexture.h);
}

void Sprite::center(const int x, const int y)
{
    m_center.x = x;
    m_center.y = y;
}

const SDL_Point &Sprite::center() const
{
    return m_center;
}

void Sprite::draw(const std::shared_ptr<Renderer> &renderer)
{
    m_windowRect.x = (int) m_position.x;
    m_windowRect.y = (int) m_position.y;

    if (m_isAnimating) {
        m_currentFrame = (m_animationClock.elapsed() / m_animationSpeed) % m_currentAnimation.frames.size();

        auto frame = m_currentAnimation.frames.at(m_currentFrame);
        m_textureRect.x = frame.x * m_textureRect.w;
        m_textureRect.y = frame.y * m_textureRect.h;
    }

    renderer->draw(m_texture, &m_textureRect, &m_windowRect, m_angle, &m_center, m_flip);
}