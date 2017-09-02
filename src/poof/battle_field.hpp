#pragma once

#include "actors.hpp"
#include "game_state.hpp"

#include <vector>

class BattleField;

class InputMapping {
public:
    InputMapping(Ship& ship, BattleField& field)
        : _ship(ship), _field(field) {}

    bool processInput(const SDL_Event& event);

private:
    Ship& _ship;
    BattleField& _field;
};

class BattleField : public GameState {
public:
    BattleField();

    void processInputEvent(const SDL_Event& event) override;
    void update(float deltaSec) override;
    void render() const override;

    void fireFromShip();

private:
    Ship _heroShip;
    std::vector<Bullet> _bullets;
    InputMapping _inputMapping;
};

