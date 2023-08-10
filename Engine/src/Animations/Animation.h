#pragma once
#include <SDL_render.h>
#include <string>

class Animation
{
public:
    Animation() {}

    void Update();
    void Draw(float x, float y, int spriteWidth, int spriteHeight, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void SetProperties(std::string textureID, int spriteRow, int frameCount, int animSpeed);

private:
    int m_SpriteRow, m_SpriteFrame;
    int m_AnimationSpeed, m_FrameCount;
    std::string m_TextureID;
};
