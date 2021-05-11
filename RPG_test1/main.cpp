#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "Player.h"

int main(int argc, char* args[]) {

    SDL_Window* window = nullptr;
    SDL_Renderer* renderTarget = nullptr;

    int currentTime = 0;
    int prevTime = 0;
    float delta = 0.0f;
    const Uint8* keyState;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("test game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    Player player1(renderTarget, "image/sprite1.png", 0, 0, 3, 4);
    Player player2(renderTarget, "image/sprite1.png", 600, 400, 3, 4);

    SDL_SetRenderDrawColor(renderTarget, 255, 255, 255, 255);

    bool isRunning = true;
    SDL_Event ev;

    while(isRunning) {

        prevTime = currentTime;
        currentTime = SDL_GetTicks();
        delta = (currentTime-prevTime) / 1000.0f;

        while(SDL_PollEvent(&ev) != 0) {
            if(ev.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        keyState = SDL_GetKeyboardState(NULL);

        player1.Update(delta, keyState);
        player2.Update(delta, keyState);

        SDL_RenderClear(renderTarget);
        player1.Draw(renderTarget);
        player2.Draw(renderTarget);
        SDL_RenderPresent(renderTarget);
    }

}
