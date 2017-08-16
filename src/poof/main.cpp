#include "screen.hpp"
#include "widgets.hpp"
#include "timer.hpp"

#include <SDL.h>

#include <vector>

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    Screen screen;

    bool done = false;

    std::vector<Button> buttons;

    buttons.emplace_back();
    buttons.back()
        .position(0.5f, 0.35f)
        .size(0.3f, 0.1f)
        .text("New Game");

    buttons.emplace_back();
    buttons.back()
        .position(0.5f, 0.5f)
        .size(0.3f, 0.1f)
        .text("Options");

    buttons.emplace_back();
    buttons.back()
        .position(0.5f, 0.65f)
        .size(0.3f, 0.1f)
        .text("Quit")
        .action([&done] {
            done = true;
        });

    Button* activeButton = nullptr;

    FrameTimer timer(60);

    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                done = true;
            } else if (event.type == SDL_MOUSEMOTION) {
                float x = event.motion.x * 1.0f / screen.width();
                float y = event.motion.y * 1.0f / screen.height();

                if (activeButton) {
                    if (!activeButton->contains(x, y)) {
                        activeButton->hoverOff();
                        activeButton = nullptr;
                    }
                }

                for (auto& button : buttons) {
                    if (button.contains(x, y)) {
                        activeButton = &button;
                        activeButton->hoverOn();
                    }
                }
            } else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                if (activeButton) {
                    activeButton->onAction();
                }
            }
        }

        if (timer.frameTime()) {
            for (auto& button : buttons) {
                button.update(timer.deltaSec());
            }

            screen.clear();
            for (const auto& button : buttons) {
                button.render(screen);
            }
            screen.present();
        }
    }

    return 0;
}