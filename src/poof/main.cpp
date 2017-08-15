#include "screen.hpp"
#include "widgets.hpp"

#include <SDL.h>

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    Screen screen;

    Button newGameButton;
    newGameButton
        .position(0.5f, 0.3f)
        .size(0.3f, 0.1f)
        .text("New Game");

    Button quitButton;
    quitButton
        .position(0.5f, 0.6f)
        .size(0.3f, 0.1f)
        .text("Quit");

    bool done = false;
    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    done = true;
                    break;
            }
        }

        screen.clear();

        newGameButton.render(screen);
        quitButton.render(screen);

        screen.present();
    }

    return 0;
}