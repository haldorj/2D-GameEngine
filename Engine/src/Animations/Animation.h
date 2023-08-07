#pragma once
#include <SDL_render.h>
#include <string>

class Animation
{
public:
    Animation() {}

    void Update();
    void Draw(float x, float y, int spriteWidth, int spriteHeight);
    void SetProperties(std::string textureID, int spriteRow, int frameCount, int animSpeed, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
    int m_SpriteRow, m_SpriteFrame;
    int m_AnimationSpeed, m_FrameCount;
    std::string m_TextureID;
    SDL_RendererFlip m_Flip;
};
