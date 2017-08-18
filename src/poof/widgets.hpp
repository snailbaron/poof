#pragma once

#include "screen.hpp"

#include <string>
#include <functional>

struct ScreenPosition {
    float x = 0.0f;
    float y = 0.0f;
    float scale = 1.0f;
};

class Widget {
public:
    virtual bool contains(float x, float y) const = 0;
    virtual void render() const = 0;
    virtual void update(float timeSec) = 0;
};

class Button : public Widget {
public:
    Button& position(float x, float y, float scale = 1.0f);
    Button& size(float width, float height);
    Button& text(std::string text);
    Button& action(std::function<void()> action);

    void hoverOn() { _hover = true; }
    void hoverOff() { _hover = false; }
    void onAction();

    bool contains(float x, float y) const override;
    void render() const override;
    void update(float timeSec) override;

private:
    ScreenPosition _position;
    float _width;
    float _height;
    std::string _text;
    bool _hover = false;
    std::function<void()> _action = []{};
};