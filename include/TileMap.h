#ifndef __TILEMAP_H__
#define __TILEMAP_H__

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <Renderer.h>
#include <PairHash.h>
#include <Vector2f.h>
#include <stdexcept>
#include <memory>
#include <string>

using namespace std::string_literals;

struct Tile
{
    SDL_Rect textureRect;
    SDL_Rect windowRect;
    int ti;
};

struct TileObject
{
    virtual ~TileObject() = default;
};

struct PlayerSpawnerObject : TileObject
{
    Vector2f position;
    PlayerSpawnerObject(const Vector2f &position);
};

class TileMap
{
private:
    SDL_Texture *m_texture;
    int m_tileSize;
    int m_textureWidth, m_textureHeight;
    std::unordered_map<std::string, std::shared_ptr<TileObject>> m_objects;
    std::unordered_map<std::pair<int, int>, Tile, PairHash> m_tiles;
public:
    TileMap(SDL_Texture *texture, const int tileSize);
    void loadMap(const std::string &mapPath);
    void addTile(const int ti, const int x, const int y);
    void addObject(const std::string &name, const std::shared_ptr<TileObject> &object);
    template <typename T>
    const std::shared_ptr<T> getObject(const std::string &name) const
    {
        auto it = m_objects.find(name);

        if (it == m_objects.end()) {
            throw std::runtime_error("TileMap: Unable to get object "s + name);
        }

        return std::dynamic_pointer_cast<T>(it->second);
    }
    void draw(const std::shared_ptr<Renderer> &renderer);
};

#endif