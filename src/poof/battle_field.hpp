#pragma once

#include "actors.hpp"
#include "game_state.hpp"

class InputMapping {
public:
    InputMapping(Ship& ship) : _ship(ship) {}

    bool processInput(const SDL_Event& event);

private:
    Ship& _ship;
};

class BattleField : public GameState {
public:
    BattleField();

    void processInputEvent(const SDL_Event& event) override;
    void update(float deltaSec) override;
    void render() const override;

private:
    Ship _heroShip;
    InputMapping _inputMapping;
};