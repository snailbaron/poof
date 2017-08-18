#include "screen.hpp"
#include "timer.hpp"
#include "game.hpp"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <vector>

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    screen::create();
    game::create();

    FrameTimer timer(60);

    bool done = false;
    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                done = true;
            } else {
                game::processInputEvent(event);
            }
        }

        // TODO: perform updates with fixed time deltas

        if (timer.frameTime()) {
            game::update(timer.deltaSec());
            game::render();
        }
    }

    screen::destroy();

    return 0;
}