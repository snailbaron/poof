#include "screen.hpp"

#include <cassert>
#include <utility>
#include <algorithm>
#include <memory>

namespace screen {

namespace {

SDL_Window* _window;
SDL_Renderer* _renderer;

} // namespace

void create()
{
    _window = SDL_CreateWindow(
        "poof",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        1024,
        768,
        SDL_WINDOW_RESIZABLE);
    assert(_window);

    _renderer = SDL_CreateRenderer(
        _window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    assert(_renderer);
}

void destroy()
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
}

int width()
{
    int w;
    SDL_GetWindowSize(_window, &w, nullptr);
    return w;
}

int height()
{
    int h;
    SDL_GetWindowSize(_window, nullptr, &h);
    return h;
}

void clear()
{
    SDL_SetRenderDrawColor(_renderer, 255, 240, 200, 255);
    SDL_RenderClear(_renderer);
}

void present()
{
    SDL_RenderPresent(_renderer);
}

void drawRect(const Rect& rect, const Color& color)
{
    SDL_SetRenderDrawColor(
        _renderer, color.r(), color.g(), color.b(), color.a());
    SDL_RenderFillRect(_renderer, rect.sdlRect());
}

void drawText(
    const std::string& text,
    res::FontId fontId,
    const Rect& rect,
    const Color& textColor)
{
    // Try to guess required font size
    int fontSize = rect.height();
    res::Font font = res::font(fontId, fontSize);

    // Correct font size based on result
    int w, h;
    TTF_SizeUTF8(font.raw(), text.c_str(), &w, &h);
    if (w > rect.width() || h > rect.height()) {
        float correction =
            std::min(rect.width() * 1.0f / w, rect.height() * 1.0f / h);
        fontSize = static_cast<int>(fontSize * correction);
        font = res::font(fontId, fontSize);
    }

    TTF_SizeUTF8(font.raw(), text.c_str(), &w, &h);
    int xOffset = std::max(0, (rect.width() - w) / 2);
    int yOffset = std::max(0, (rect.height() - h) / 2);

    SDL_Surface* surface =
        TTF_RenderUTF8_Blended(font.raw(), text.c_str(), textColor.sdlColor());

    SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, surface);
    SDL_Rect srcRect {0, 0, surface->w, surface->h};
    SDL_Rect dstRect {
        rect.x() + xOffset,
        rect.y() + yOffset,
        surface->w,
        surface->h};
    SDL_RenderCopy(_renderer, texture, &srcRect, &dstRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void drawTexture(const res::Texture& texture, const ScreenPosition& position)
{
    SDL_Rect dst {
        position.x - texture.width() / 2,
        position.y - texture.height() / 2,
        texture.width(),
        texture.height()};
    SDL_RenderCopy(_renderer, texture.raw(), nullptr, &dst);
}

SDL_Renderer* renderer()
{
    return _renderer;
}

} // namespace screen
