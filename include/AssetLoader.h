#ifndef __ASSET_LOADER_H__
#define __ASSET_LOADER_H__

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <AtlasReader.h>
#include <unordered_map>
#include <functional>
#include <Renderer.h>
#include <memory>
#include <string>
#include <vector>

enum AssetType
{
    ASSET_TYPE_TEXTURE,
    ASSET_TYPE_ATLAS,
    ASSET_TYPE_FONT,
    ASSET_TYPE_SFX,
    ASSET_TYPE_MUSIC
};

struct Asset
{
    AssetType type;
    std::string id;
    std::string path;
    
    Asset(const AssetType &type, const std::string &id, const std::string &path);
    virtual ~Asset() = default;
};

struct AssetFont : Asset
{
    unsigned int fontSize;
    
    AssetFont(const std::string &id, const std::string &path, const unsigned int fontSize);
};

class AssetLoader
{
private:
    bool m_loading;
    unsigned int m_loadedAssets;
    SDL_Renderer *m_renderer;
    std::vector<std::shared_ptr<Asset>> m_assets;
    std::unordered_map<std::string, SDL_Texture*> m_textures;
    std::unordered_map<std::string, Atlas> m_atlases;
    std::unordered_map<std::string, TTF_Font*> m_fonts;
    std::unordered_map<std::string, Mix_Chunk*> m_soundEffects;;
    std::unordered_map<std::string, Mix_Music*> m_music;

public:
    AssetLoader(const std::shared_ptr<Renderer> &renderer);
    ~AssetLoader();
    SDL_Texture *getTexture(const std::string &id);
    const Atlas &getAtlas(const std::string &id);
    TTF_Font *getFont(const std::string &id);
    Mix_Chunk *getSfx(const std::string &id);
    Mix_Music *getMusic(const std::string &id);
    void addAsset(const std::shared_ptr<Asset> &asset);
    void addTexture(const std::string &id, const std::string &path);
    void addAtlas(const std::string &id, const std::string &path);
    void addFont(const std::string &id, const std::string &path, const unsigned int fontSize = 12);
    void addSfx(const std::string &id, const std::string &path);
    void addMusic(const std::string &id, const std::string &path);
    void load(std::function<void()> cb);
};

#endif