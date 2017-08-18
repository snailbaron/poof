#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

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
};

class Texture {
public:
    Texture(const std::string& texturePath);

    SDL_Texture* raw() const { return _texture.get(); }

private:
    std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> _texture;
};

} // namespace res