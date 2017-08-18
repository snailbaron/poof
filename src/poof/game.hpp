#pragma once

#include "game_state.hpp"
#include "main_menu.hpp"
#include "battle_field.hpp"

#include <memory>

namespace game {

void create();

void processInputEvent(const SDL_Event& event);
void update(float deltaSec);
void render();

template <class State> void transitionToState();

extern template void transitionToState<MainMenu>();
extern template void transitionToState<BattleField>();

} // namespace game