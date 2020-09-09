#include <nlohmann/json.hpp>
#include <AtlasReader.h>
#include <fstream>
#include <Log.h>

using json = nlohmann::json;

AtlasReader::AtlasReader(const std::string &path)
{
    std::ifstream f(path);
    json json = json::parse(f);  

    auto &jsonAtlas = json["atlas"];

    std::string id = jsonAtlas["id"];
    std::string defaultAnimation = jsonAtlas["defaultAnimation"];

    m_atlas.id = id;
    m_atlas.defaultAnimation = defaultAnimation;

    if (jsonAtlas["textures"].is_null()) {
        LOG_ERROR("[" << path << "] Missing textures block from atlas file.");
    }

    auto &textures = jsonAtlas["textures"];

    for (auto it = textures.begin(); it != textures.end(); ++it) {
        std::string key = it.key();
        auto value = it.value();

        std::string src = value["src"];
        unsigned int w = value["w"];
        unsigned int h = value["h"];
        
        m_atlas.textures.insert({id, { key, src, w, h }});
    }

    if (!jsonAtlas["animations"].is_null()) {
        auto &animations = jsonAtlas["animations"];

        for (auto it = animations.begin(); it != animations.end(); ++it) {
            std::string key = it.key();
            auto value = it.value();

            std::string texture_id = value["texture_id"];
            std::vector<AtlasAnimationFrame> animationFrames;

            if (!value["frames"].is_null()) {
                auto &frames = value["frames"];

                for (auto jit = frames.begin(); jit != frames.end(); ++jit) {
                    auto jvalue = jit.value();
                    unsigned int x = jvalue["x"];
                    unsigned int y = jvalue["y"];

                    animationFrames.push_back({x, y});
                }
            }

            m_atlas.animations.insert({key, { key, texture_id, animationFrames }});
        }
    }
}

const Atlas &AtlasReader::atlas()
{
    return m_atlas;
}