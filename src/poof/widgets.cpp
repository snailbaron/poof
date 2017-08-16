#include "widgets.hpp"
#include "resources.hpp"

#include <SDL_ttf.h>

#include <utility>
#include <algorithm>

Button& Button::position(float x, float y, float scale)
{
    _position.x = x;
    _position.y = y;
    _position.scale = scale;
    return *this;
}

Button& Button::size(float width, float height)
{
    _width = width;
    _height = height;
    return *this;
}

Button& Button::text(std::string text)
{
    _text = std::move(text);
    return *this;
}

Button& Button::action(std::function<void()> action)
{
    _action = std::move(action);
    return *this;
}

void Button::onAction()
{
    _action();
}

bool Button::contains(float x, float y) const
{
    return x >= _position.x - _width * _position.scale / 2 &&
        x <= _position.x + _width * _position.scale / 2 &&
        y >= _position.y - _height * _position.scale / 2 &&
        y <= _position.y + _height * _position.scale / 2;
}

void Button::render(Screen& screen) const
{
    float frameScale = _position.scale;
    Color frameColor {100, 100, 100};
    Color bgColor { 200, 100, 80 };
    Color textColor { 0, 0, 0 };

    Rect outerRect(
        static_cast<int>((_position.x - _width / 2.0f * frameScale) * screen.width()),
        static_cast<int>((_position.y - _height / 2.0f * frameScale) * screen.height()),
        static_cast<int>(_width * frameScale * screen.width()),
        static_cast<int>(_height * frameScale * screen.height()));

    screen.drawRect(outerRect, frameColor);

    int frameWidth = static_cast<int>(
        std::min(screen.width(), screen.height()) * 0.01f);

    Rect innerRect(
        outerRect.x() + frameWidth,
        outerRect.y() + frameWidth,
        outerRect.width() - 2 * frameWidth,
        outerRect.height() - 2 * frameWidth);

    int padding = frameWidth;
    Rect textRect(
        innerRect.x() + padding,
        innerRect.y() + padding,
        innerRect.width() - 2 * padding,
        innerRect.height() - 2 * padding);

    screen.drawRect(innerRect, bgColor);

    screen.drawText(_text, res::FontId::Fyodor, textRect, textColor);
}

void Button::update(float timeSec)
{
    if (_hover) {
        _position.scale = std::min(1.1f, _position.scale + timeSec * 0.8f);
    } else {
        _position.scale = std::max(1.0f, _position.scale - timeSec * 0.8f);
    }
}