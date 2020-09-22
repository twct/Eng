#include <AssetLoader.h>
#include <stdexcept>
#include <sstream>
#include <Log.h>

using namespace std::string_literals;

Asset::Asset(const AssetType &type, const std::string &id, const std::string &path) :
    type(type),
    id(id),
    path(path)
{
}

AssetFont::AssetFont(const std::string &id, const std::string &path, const unsigned int fontSize) :
    Asset(AssetType::Font, id, path),
    fontSize(fontSize)
{
}

AssetLoader::AssetLoader(const std::shared_ptr<Renderer> &renderer) :
    m_renderer(renderer->renderer())
{
    m_loading = true;
    m_loadedAssets = 0;
}

AssetLoader::~AssetLoader()
{
    for (auto &[key, texture] : m_textures) {
        SDL_DestroyTexture(texture);
    }

    for (auto &[key, font] : m_fonts) {
        TTF_CloseFont(font);
    }

    m_textures.clear();
    m_atlases.clear();
    m_fonts.clear();
}

SDL_Texture *AssetLoader::getTexture(const std::string &id)
{
    auto it = m_textures.find(id);

    if (it == m_textures.end()) {
        throw std::runtime_error("Unable to find texture: "s + id);
    }

    return it->second;
}

const Atlas &AssetLoader::getAtlas(const std::string &id)
{
    auto it = m_atlases.find(id);

    if (it == m_atlases.end()) {
        throw std::runtime_error("Unable to find atlas: "s + id);
    }

    return it->second;
}

TTF_Font *AssetLoader::getFont(const std::string &id)
{
    auto it = m_fonts.find(id);

    if (it == m_fonts.end()) {
        throw std::runtime_error("Unable to find font: "s + id);
    }

    return it->second;
}

Mix_Chunk *AssetLoader::getSfx(const std::string &id)
{
    auto it = m_soundEffects.find(id);

    if (it == m_soundEffects.end()) {
        throw std::runtime_error("Unable to find sound effect: "s + id);
    }

    return it->second;
}

Mix_Music *AssetLoader::getMusic(const std::string &id)
{
    auto it = m_music.find(id);

    if (it == m_music.end()) {
        throw std::runtime_error("Unable to find music: "s + id);
    }

    return it->second;
}

void AssetLoader::addAsset(const std::shared_ptr<Asset> &asset)
{
#if (!TARGET_OS_IPHONE)
    std::ostringstream path_oss;
    path_oss << "resources/" << asset->path;
    asset->path = path_oss.str();
#endif

    m_assets.push_back(asset);
}

void AssetLoader::addTexture(const std::string &id, const std::string &path)
{
    addAsset(std::make_shared<Asset>(AssetType::Texture, id, path));
}

void AssetLoader::addAtlas(const std::string &id, const std::string &path)
{
    addAsset(std::make_shared<Asset>(AssetType::Atlas, id, path));
}

void AssetLoader::addFont(const std::string &id, const std::string &path, const unsigned int fontSize)
{
    addAsset(std::make_shared<AssetFont>(id, path, fontSize));
}

void AssetLoader::addSfx(const std::string &id, const std::string &path)
{
    addAsset(std::make_shared<Asset>(AssetType::SoundEffect, id, path));
}

void AssetLoader::addMusic(const std::string &id, const std::string &path)
{
    addAsset(std::make_shared<Asset>(AssetType::Music, id, path));
}

void AssetLoader::load(const std::function<void()> &&cb)
{
    if (m_assets.size() <= 0) {
        cb();
        m_loading = false;
        return;
    }   

    auto asset = m_assets.at(m_loadedAssets);

    switch (asset->type) {
        case AssetType::Texture:
        {
            SDL_Texture *texture = IMG_LoadTexture(m_renderer, asset->path.c_str());

            if (!texture) {
                LOG_ERROR("Unable to load texture: " << asset->id);
                break;
            }

            LOG_INFO("Loaded texture: " << asset->id);
            m_textures.insert({asset->id, texture});
        }
        break;
        case AssetType::Atlas:
        {
            std::shared_ptr<AtlasReader> reader = std::make_shared<AtlasReader>(asset->path);

            auto &atlas = reader->atlas();

            LOG_INFO("Loaded atlas: " << asset->id);
            
            for (auto &[key, value]: atlas.textures) {
                this->addTexture(key, value.path);
            }

            m_atlases.insert({asset->id, atlas});
        }
        break;
        case AssetType::Font:
        {
            auto assetFont = std::dynamic_pointer_cast<AssetFont>(asset);

            TTF_Font *font = TTF_OpenFont(assetFont->path.c_str(), assetFont->fontSize);

            if (!font) {
                LOG_ERROR("Unable to load font: " << asset->id);
                break;
            }

            LOG_INFO("Loaded font: " << assetFont->id);
            m_fonts.insert({assetFont->id, font});
        }
        case AssetType::SoundEffect:
        {
            Mix_Chunk *chunk = Mix_LoadWAV(asset->path.c_str());

            if (!chunk) {
                LOG_ERROR("Unable to load sound effect: " << asset->id);
                break;
            }

            m_soundEffects.insert({asset->id, chunk});
        }
        break;
        case AssetType::Music:
        {
            Mix_Music *music = Mix_LoadMUS(asset->path.c_str());

            if (!music) {
                LOG_ERROR("Unable to load music: " << asset->id);
                break;
            }

            m_music.insert({asset->id, music});
        }
        break;
    }

    ++m_loadedAssets;

    if (m_loadedAssets >= m_assets.size()) {
        cb();
        m_loading = false;
    }
}

const bool AssetLoader::loading() const
{
    return m_loading;
}

const unsigned int AssetLoader::loadedAssets() const
{
    return m_loadedAssets;
}

const unsigned int AssetLoader::totalAssets() const
{
    return m_assets.size();
}