#include "game.hpp"
#include "main_menu.hpp"

namespace game {

namespace {

std::unique_ptr<GameState> _state;

} // namespace

void create()
{
    _state = std::make_unique<MainMenu>();
}

void processInputEvent(const SDL_Event& event)
{
    _state->processInputEvent(event);
}

void update(float deltaSec)
{
    _state->update(deltaSec);
}

void render()
{
    _state->render();
}

template <class State> void transitionToState()
{
    _state = std::make_unique<State>();
}

template void transitionToState<MainMenu>();
template void transitionToState<BattleField>();

} // namespace game