#pragma once

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

} // namespace res