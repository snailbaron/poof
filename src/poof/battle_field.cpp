#include "battle_field.hpp"
#include "screen.hpp"

bool InputMapping::processInput(const SDL_Event& event)
{
    if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
        bool press = event.type == SDL_KEYDOWN;

        switch (event.key.keysym.sym) {
        case SDLK_w:
            _ship.inputY = press ? -1.f : 0.f;
            break;
        case SDLK_s:
            _ship.inputY = press ? 1.f : 0.f;
            break;
        case SDLK_a:
            _ship.inputX = press ? -1.f : 0.f;
            break;
        case SDLK_d:
            _ship.inputX = press ? 1.f : 0.f;
            break;
        default:
            return false;
        }

        return true;
    }

    return false;
}

BattleField::BattleField()
    : _heroShip()
    , _inputMapping(_heroShip)
{
    _heroShip.position.x = 500.f;
    _heroShip.position.y = 500.f;
}

void BattleField::processInputEvent(const SDL_Event& event)
{
    _inputMapping.processInput(event);
}

void BattleField::update(float deltaSec)
{
    _heroShip.update(deltaSec);
}

void BattleField::render() const
{
    screen::clear();

    _heroShip.render();

    screen::present();
}
