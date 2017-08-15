#pragma once

#include "screen.hpp"

#include <string>

struct Position {
    float x = 0.0f;
    float y = 0.0f;
    float scale = 1.0f;
};

class Widget {
public:
    virtual void render(Screen& screen) = 0;
};

class Button : public Widget {
public:
    Button() {}

    Button& position(float x, float y, float scale = 1.0f);
    Button& size(float width, float height);
    Button& text(std::string text);

    void render(Screen& screen) override;

private:
    Position _position;
    float _width;
    float _height;
    std::string _text;
};