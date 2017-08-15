#pragma once

#include "resources.hpp"

#include <SDL.h>

#include <cstdint>
#include <string>

struct SDL_Window;
struct SDL_Renderer;

class Color {
public:
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
        : _color{r, g, b, a}
    { }

    uint8_t& r() { return _color.r; }
    uint8_t r() const { return _color.r; }

    uint8_t& g() { return _color.g; }
    uint8_t g() const { return _color.g; }

    uint8_t& b() { return _color.b; }
    uint8_t b() const { return _color.b; }

    uint8_t& a() { return _color.a; }
    uint8_t a() const { return _color.a; }

    const SDL_Color& sdlColor() const { return _color; }
    SDL_Color& sdlColor() { return _color; }

private:
    SDL_Color _color;
};

class Rect {
public:
    Rect(int x, int y, int width, int height)
        : _rect{x, y, width, height}
    { }

    int& x() { return _rect.x; }
    int x() const { return _rect.x; }

    int& y() { return _rect.y; }
    int y() const { return _rect.y; }

    int& width() { return _rect.w; }
    int width() const { return _rect.w; }

    int& height() { return _rect.h; }
    int height() const { return _rect.h; }

    const SDL_Rect* sdlRect() const { return &_rect; }
    SDL_Rect* sdlRect() { return &_rect; }

private:
    SDL_Rect _rect;
};

class Screen {
public:
    Screen();
    ~Screen();

    Screen(Screen&& other) noexcept;
    Screen& operator=(Screen&& other) noexcept;

    Screen(const Screen& other) = delete;
    Screen& operator=(const Screen& other) = delete;

    int width() const;
    int height() const;

    void clear();
    void present();

    void drawRect(const Rect& rect, const Color& color);
    void drawText(
        const std::string& text,
        res::FontId font,
        const Rect& rect,
        const Color& textColor);

    // TODO: remove the need to use this function
    SDL_Renderer* renderer() const { return _renderer; }

private:
    SDL_Window* _window;
    SDL_Renderer* _renderer;
};
