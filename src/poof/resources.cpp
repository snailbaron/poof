#include "resources.hpp"

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

} // namespace

Font::Font(const std::string& fontPath, int ptSize)
{
    TTF_Font* rawFont = TTF_OpenFont(fontPath.c_str(), ptSize);
    assert(rawFont);
    _font.reset(rawFont, TTF_CloseFont);
}

void load()
{
    // TODO
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

} // namespace res