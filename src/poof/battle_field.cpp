#include "battle_field.hpp"
#include "screen.hpp"

#include <iostream>

bool InputMapping::processInput(const SDL_Event& event)
{
    if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
        bool press = event.type == SDL_KEYDOWN;

        switch (event.key.keysym.sym) {
        case SDLK_w:
            _ship.input.y = press ? -1.f : 0.f;
            break;
        case SDLK_s:
            _ship.input.y = press ? 1.f : 0.f;
            break;
        case SDLK_a:
            _ship.input.x = press ? -1.f : 0.f;
            break;
        case SDLK_d:
            _ship.input.x = press ? 1.f : 0.f;
            break;
        default:
            return false;
        }

        return true;
    }

    if (event.type == SDL_MOUSEBUTTONDOWN) {
        _field.fireFromShip();
    }

    return false;
}

BattleField::BattleField()
    : _heroShip()
    , _inputMapping(_heroShip, *this)
{
    _heroShip.positionMeters.x = 10.f;
    _heroShip.positionMeters.y = 10.f;
}

void BattleField::processInputEvent(const SDL_Event& event)
{
    _inputMapping.processInput(event);
}

void BattleField::update(float deltaSec)
{
    _heroShip.update(deltaSec);
    for (auto& bullet : _bullets) {
        bullet.update(deltaSec);
    }

    // Remove bullets out of screen
    for (auto i = _bullets.begin(); i != _bullets.end();) {
        const auto& position = i->position;
        if (position.x < -20.f || position.x > 120.f ||
                position.y < -20.f || position.y > 120.f) {
            i = _bullets.erase(i);
        } else {
            i++;
        }
    }
}

void BattleField::render() const
{
    screen::clear();

    _heroShip.render();
    for (const auto& bullet : _bullets) {
        bullet.render();
    }

    screen::present();
}

void BattleField::fireFromShip()
{
    _bullets.emplace_back(
        _heroShip.positionMeters,
        Vector<float>{0.f, -50.f});
}