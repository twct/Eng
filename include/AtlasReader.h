#ifndef __ATLAS_READER_H__
#define __ATLAS_READER_H__

#include <unordered_map>
#include <string>
#include <vector>

struct AtlasTexture
{
    std::string id;
    std::string path;
    unsigned int w, h;
};

struct AtlasAnimationFrame
{
    unsigned int x;
    unsigned int y;
};

struct AtlasAnimation
{
    std::string id;
    std::string texture_id;
    
    std::vector<AtlasAnimationFrame> frames;
};

struct Atlas
{
    std::string id;
    std::string defaultAnimation;
    std::unordered_map<std::string, AtlasTexture> textures;
    std::unordered_map<std::string, AtlasAnimation> animations;
};

class AtlasReader
{
public:
    AtlasReader(const std::string &path);
    const Atlas &atlas();
private:
    Atlas m_atlas;
};

#endif