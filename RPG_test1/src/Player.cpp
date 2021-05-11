#include "Player.h"
#include <SDL_image.h>
#include <iostream>


Player::Player(SDL_Renderer* renderTarget, std::string filePath, int x, int y, int framesX, int framesY)
{
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if(surface == NULL) {
        std::cout << "Error 1" << std::endl;
    } else {
        texture = SDL_CreateTextureFromSurface(renderTarget, surface);
        if (texture == NULL) {
            std::cout << "Error 2" << std::endl;
        }
    }

    SDL_FreeSurface(surface);

    SDL_QueryTexture(texture, NULL, NULL, &cropRect.w, &cropRect.h);

    positionRect.x = x;
    positionRect.y = y;

    textureWidth = cropRect.w;

    cropRect.w /= framesX;
    cropRect.h /= framesY;

    frameWidth = positionRect.w = cropRect.w;
    frameHeight = positionRect.h = cropRect.h;

    isActive = false;

    static int playerNumber = 0;
    playerNumber++;

    if(playerNumber == 1) {
        keys[0] = SDL_SCANCODE_W;
        keys[1] = SDL_SCANCODE_S;
        keys[2] = SDL_SCANCODE_A;
        keys[3] = SDL_SCANCODE_D;
    } else {
        keys[0] = SDL_SCANCODE_UP;
        keys[1] = SDL_SCANCODE_DOWN;
        keys[2] = SDL_SCANCODE_LEFT;
        keys[3] = SDL_SCANCODE_RIGHT;
    }

    moveSpeed = 200.0f;
}

Player::~Player()
{
    SDL_DestroyTexture(texture);
}

void Player::Update(float delta, const Uint8* keyState) {

    isActive = true;

    if(keyState[keys[0]]) {
        cropRect.y = frameHeight*3;
        positionRect.y -= (int)(moveSpeed * delta);
    } else if(keyState[keys[1]]) {
        cropRect.y = frameHeight*0;
        positionRect.y += (int)(moveSpeed * delta);
    } else if(keyState[keys[2]]) {
        cropRect.y = frameHeight*1;
        positionRect.x -= (int)(moveSpeed * delta);
    } else if(keyState[keys[3]]) {
        cropRect.y = frameHeight*2;
        positionRect.x += (int)(moveSpeed * delta);
    } else {
        isActive = false;
    }

    if(isActive) {
        frameCounter += delta;

        if(frameCounter >= 0.25f) {
            frameCounter = 0;
            cropRect.x += frameWidth;
            if(cropRect.x >= textureWidth) {
                cropRect.x = 0;
            }
        }
    } else {
        frameCounter = 0;
        cropRect.x = frameWidth;
    }
}

void Player::Draw(SDL_Renderer* renderTarget) {
    SDL_RenderCopy(renderTarget, texture, &cropRect, &positionRect);
}
