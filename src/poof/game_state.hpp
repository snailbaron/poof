#pragma once

#include "sdl_libs.hpp"

class GameState {
public:
    virtual void processInputEvent(const SDL_Event& event) = 0;
    virtual void update(float deltaSec) = 0;
    virtual void render() const = 0;
};
