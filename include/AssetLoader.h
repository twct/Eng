#ifndef __ASSET_LOADER_H__
#define __ASSET_LOADER_H__

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include <unordered_map>
#include <functional>
#include <Renderer.h>
#include <memory>
#include <string>
#include <vector>

enum AssetType
{
    ASSET_TYPE_TEXTURE,
    ASSET_TYPE_FONT
};

struct Asset
{
    AssetType type;
    std::string id;
    std::string path;
    
    Asset(const AssetType &type, const std::string &id, const std::string &path);
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
public:
    AssetLoader(const std::shared_ptr<Renderer> &renderer);
    ~AssetLoader();
    void addAsset(const std::shared_ptr<Asset> &asset);
    void addTexture(const std::string &id, const std::string &path);
    void addFont(const std::string &id, const std::string &path, const unsigned int fontSize = 12);
    void load(std::function<void()> cb);
};

#endif