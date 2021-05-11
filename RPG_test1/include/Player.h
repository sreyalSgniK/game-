#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <string>

class Player
{
private:
    SDL_Rect cropRect;
    SDL_Rect positionRect;
    SDL_Texture* texture;
    float moveSpeed;
    float frameCounter;
    int frameWidth, frameHeight;
    int textureWidth;
    bool isActive;
    SDL_Scancode keys[4];
public:
    Player(SDL_Renderer* renderTarget, std::string filePath, int x, int y, int framesX, int framesY);
    virtual ~Player();

    void Update(float delta, const Uint8* keyState);
    void Draw(SDL_Renderer* renderTarget);

};

#endif // PLAYER_H
