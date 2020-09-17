#include <nlohmann/json.hpp>
#include <TileMap.h>
#include <sstream>
#include <fstream>
#include <Log.h>

using json = nlohmann::json;

PlayerSpawnerObject::PlayerSpawnerObject(const Vector2f &position) :
    position(position)
{
}

TileMap::TileMap(SDL_Texture *texture, const int tileSize) :
    m_texture(texture),
    m_tileSize(tileSize)
{
    SDL_QueryTexture(m_texture, nullptr, nullptr, &m_textureWidth, &m_textureHeight);
}

void TileMap::loadMap(const std::string &mapPath)
{
    std::ostringstream path;
    path << "resources/" << mapPath;

    std::ifstream f(path.str());

    if (f.fail()) {
        throw std::runtime_error("Unable to find map file: "s + mapPath);
    }

    LOG_INFO("Load map: " << mapPath);

    json json = json::parse(f);

    int layeri = 0;

    auto &layers = json["layers"];

    for (auto &layer : layers) {
        auto type = layer["type"];

        if (type == "objectgroup") {
            for (auto &object : layer["objects"]) {
                auto type = object["type"];
                if (type == "PlayerSpawner") {
                    addObject(type, std::make_shared<PlayerSpawnerObject>(Vector2f(object["x"], object["y"])));
                }
            }
        }
        else if (type == "tilelayer") {
            const int startX = layer["startx"];
            const int startY = layer["starty"];

            for (auto &chunk : layer["chunks"]) {
                const int width = chunk["width"];
                const int height = chunk["height"];
                int cx = chunk["x"];
                int cy = chunk["y"];
                int tx = cx;
                int ty = cy;

                for (auto &t : chunk["data"]) {
                    if (t != 0) {
                        addTile(t, tx, ty);
                    }
                    ++tx;
                    if (tx >= cx + width) {
                        tx = cx;
                        ++ty;
                    }
                }
            }
        }
    }
}

void TileMap::addTile(const int ti, const int x, const int y)
{
    const int index = ti - 1;
    const int totalColumns = m_textureWidth / m_tileSize;

    const int tx = index % totalColumns;
    const int ty = ceil(index / totalColumns);

    Tile tile;
    tile.textureRect = {tx * m_tileSize, ty * m_tileSize, m_tileSize, m_tileSize};
    tile.windowRect = {x * m_tileSize, y * m_tileSize, m_tileSize, m_tileSize};
    tile.ti = index;

    m_tiles.insert({{x, y}, tile});
}

void TileMap::addObject(const std::string &name, const std::shared_ptr<TileObject> &object)
{
    m_objects.insert({name, object});
}

void TileMap::draw(const std::shared_ptr<Renderer> &renderer)
{
    auto cameraBounds = renderer->camera().bounds();

    const int sx = ceil(cameraBounds.x / m_tileSize);
    const int sy = ceil(cameraBounds.y / m_tileSize);
    const int w = ceil(cameraBounds.w / m_tileSize) + 1;
    const int h = ceil(cameraBounds.h / m_tileSize) + 1;

    for (int x = sx; x < sx + w + 1; ++x) {
        for (int y = sy - 1; y < sy + h + 1; ++y) {
            auto it = m_tiles.find({x, y});
            if (it != m_tiles.end()) {
                auto &t = it->second;
                renderer->draw(m_texture, &t.textureRect, &t.windowRect);
            }
        }
    }
}