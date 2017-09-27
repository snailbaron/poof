#pragma once

#include "widgets.hpp"
#include "screen.hpp"
#include "game_state.hpp"

#include "sdl_libs.hpp"

#include <vector>

class MainMenu : public GameState {
public:
    MainMenu();

    void processInputEvent(const SDL_Event& event) override;
    void update(float deltaSec) override;
    void render() const override;

private:
    std::vector<Button> _buttons;
    Button* _activeButton = nullptr;
};
