#include "main_menu.hpp"
#include "game.hpp"
#include "battle_field.hpp"

MainMenu::MainMenu()
{
    _buttons.emplace_back();
    _buttons.back()
        .position(0.5f, 0.35f)
        .size(0.3f, 0.1f)
        .text("New Game")
        .action([] {
            game::transitionToState<BattleField>();
        });

    _buttons.emplace_back();
    _buttons.back()
        .position(0.5f, 0.5f)
        .size(0.3f, 0.1f)
        .text("Options");

    _buttons.emplace_back();
    _buttons.back()
        .position(0.5f, 0.65f)
        .size(0.3f, 0.1f)
        .text("Quit")
        .action([] {
            SDL_Event quitEvent;
            quitEvent.type = SDL_QUIT;
            SDL_PushEvent(&quitEvent);
        });
}

void MainMenu::processInputEvent(const SDL_Event& event)
{
    if (event.type == SDL_MOUSEMOTION) {
        float x = event.motion.x * 1.0f / screen::width();
        float y = event.motion.y * 1.0f / screen::height();

        if (_activeButton) {
            if (!_activeButton->contains(x, y)) {
                _activeButton->hoverOff();
                _activeButton = nullptr;
            }
        }

        for (auto& button : _buttons) {
            if (button.contains(x, y)) {
                _activeButton = &button;
                _activeButton->hoverOn();
            }
        }
    } else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
        if (_activeButton) {
            _activeButton->onAction();
        }
    }
}

void MainMenu::update(float deltaSec)
{
    for (auto& button : _buttons) {
        button.update(deltaSec);
    }
}

void MainMenu::render() const
{
    screen::clear();
    for (const auto& button : _buttons) {
        button.render();
    }
    screen::present();
}
