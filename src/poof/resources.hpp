#pragma once

#include "sdl_libs.hpp"

#include <memory>
#include <string>

namespace res {

// Load resources for the whole game
void load();

enum FontId {
    Fyodor,
};

class Font {
public:
    Font(const std::string& fontPath, int ptSize);

    TTF_Font* raw() const { return _font.get(); }

private:
    std::shared_ptr<TTF_Font> _font;
};

Font font(FontId id, int ptSize);

enum TextureId {
    Ship,
    Bullet,
};

class Texture {
public:
    Texture(const std::string& texturePath);

    int width() const { return _width; }
    int height() const { return _height; }
    SDL_Texture* raw() const { return _texture.get(); }

private:
    std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> _texture;
    int _width;
    int _height;
};

const Texture& texture(TextureId textureId);

} // namespace res
