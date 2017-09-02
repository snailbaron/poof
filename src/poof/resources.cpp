#include "resources.hpp"
#include "screen.hpp"

#include <SDL_image.h>

#include <map>
#include <cassert>
#include <tuple>

namespace res {

namespace {

std::map<FontId, std::string> fontPaths {
    { Fyodor, "fonts/fyodor/Fyodor-Bold.ttf" },
};

struct FontAndSize {
    FontId font;
    int ptSize;
};

bool operator<(const FontAndSize& left, const FontAndSize& right)
{
    return std::tie(left.font, left.ptSize) <
        std::tie(right.font, right.ptSize);
}

std::map<FontAndSize, Font> fontCache;

std::map<TextureId, std::string> texturePaths {
    { Ship, "bitmaps/ship.png" },
    { Bullet, "bitmaps/bullet.png" },
};

std::map<TextureId, Texture> textureCache;

} // namespace

Font::Font(const std::string& fontPath, int ptSize)
{
    TTF_Font* rawFont = TTF_OpenFont(fontPath.c_str(), ptSize);
    assert(rawFont);
    _font.reset(rawFont, TTF_CloseFont);
}

void load()
{
    // Load textures
    for (const auto& texturePathPair : texturePaths) {
        textureCache.insert(
            {texturePathPair.first, Texture(texturePathPair.second)});
    }
}

Font font(FontId id, int ptSize)
{
    const std::string& path = fontPaths[id];

    auto it = fontCache.find({id, ptSize});
    if (it != fontCache.end()) {
        return it->second;
    }

    Font font(path, ptSize);
    fontCache.emplace(FontAndSize{id, ptSize}, font);

    return font;
}

Texture::Texture(const std::string& texturePath)
    : _texture(nullptr, SDL_DestroyTexture)
    , _width(0)
    , _height(0)
{
    SDL_Surface* surface = IMG_Load(texturePath.c_str());
    assert(surface);
    _width = surface->w;
    _height = surface->h;

    SDL_Texture* texture =
        SDL_CreateTextureFromSurface(screen::renderer(), surface);
    assert(texture);

    _texture.reset(texture);

    SDL_FreeSurface(surface);
}

const Texture& texture(TextureId textureId)
{
    assert(textureCache.find(textureId) != textureCache.end());
    return textureCache.at(textureId);
}

} // namespace res