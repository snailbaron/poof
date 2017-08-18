#include "battle_field.hpp"
#include "screen.hpp"

BattleField::BattleField()
{ }

void BattleField::processInputEvent(const SDL_Event& event)
{
}

void BattleField::update(float deltaSec)
{
}

void BattleField::render() const
{
    screen::clear();

    screen::drawText("The game should be here, but it is not implemented",
        res::FontId::Fyodor,
        Rect(0, screen::height() / 3, screen::width(), screen::height() / 3),
        Color(0, 0, 0));

    screen::present();
}
