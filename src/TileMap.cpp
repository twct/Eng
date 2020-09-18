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
                        addCollider(tx, ty);
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

void TileMap::addCollider(const int x, const int y)
{
    Collider collider(m_tileSize, m_tileSize);
    collider.update({(float) x * m_tileSize, (float) y * m_tileSize});

    m_colliders.insert({{x, y}, collider});
}

const std::unordered_map<std::pair<int, int>, Collider, PairHash> &TileMap::colliders()
{
    return m_colliders;
}

const std::vector<Collider> TileMap::nearbyColliders(const Vector2i &position, std::vector<Collider> vec) const
{
    const int x = position.x / m_tileSize;
    const int y = position.y / m_tileSize;

    SDL_Point points[] = {
        {x - 1, y - 1}, {x, y - 1}, {x + 1, y - 1},
        {x - 1, y}, {x, y}, {x + 1, y},
        {x - 1, y + 1}, {x, y + 1}, {x + 1, y + 1}
    };

    for (auto &point : points) {
        auto it = m_colliders.find({point.x, point.y});
        if (it != m_colliders.end()) {
            vec.push_back(it->second);
        }
    }

    return vec;
}

const std::vector<Collider> TileMap::nearbyColliders(const Collider &c) const
{
    auto rect = c.rect();

    if (rect.w > m_tileSize || rect.h > m_tileSize) {
        const int xlimit = rect.w / m_tileSize;
        const int ylimit = rect.h / m_tileSize;

        std::vector<Collider> vec;

        for (int x = 0; x < xlimit; ++x) {
            for (int y = 0; y < ylimit; ++y) {
                vec = nearbyColliders({rect.x + (x * m_tileSize), rect.y + (y * m_tileSize)}, vec);
            }
        }

        return vec;
    }

    return nearbyColliders(Vector2i(rect.x, rect.y));
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