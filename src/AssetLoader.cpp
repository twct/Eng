#include <AssetLoader.h>
#include <sstream>
#include <Log.h>

Asset::Asset(const AssetType &type, const std::string &id, const std::string &path) :
    type(type),
    id(id),
    path(path)
{
}

AssetFont::AssetFont(const std::string &id, const std::string &path, const unsigned int fontSize) :
    Asset(ASSET_TYPE_FONT, id, path),
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
    //
}

void AssetLoader::addAsset(const std::shared_ptr<Asset> &asset)
{
#if (!TARGET_OS_IPHONE)
    std::ostringstream path_oss;
    path_oss << "resources/" << asset->path;
#endif

    m_assets.push_back(asset);
}

void AssetLoader::addFont(const std::string &id, const std::string &path, const unsigned int fontSize)
{
    addAsset(std::make_shared<AssetFont>(id, path, fontSize));
}

void AssetLoader::addTexture(const std::string &id, const std::string &path)
{
    addAsset(std::make_shared<Asset>(ASSET_TYPE_TEXTURE, id, path));
}

void AssetLoader::load(std::function<void()> cb)
{
    if (m_assets.size() <= 0) {
        cb();
        m_loading = false;
    }   

    auto asset = m_assets.at(m_loadedAssets);

    switch (asset->type) {
        case ASSET_TYPE_TEXTURE:
        {
            SDL_Texture *texture = IMG_LoadTexture(m_renderer, asset->path.c_str());

            if (!texture) {
                LOG_ERROR("Unable to load texture: " << asset->id);
                break;
            }

            m_textures.insert({asset->id, texture});
        }
        break;
        case ASSET_TYPE_FONT:
        {
            // auto assetFont = std::dynamic_pointer_cast<AssetFont>(asset);
        }
    }
}