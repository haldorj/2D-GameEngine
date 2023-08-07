#pragma once

#include <SDL_render.h>

#include "IObject.h"
#include "../Physics/Transform.h"

struct Properties
{
    Properties(std::string textureID, int posx, int posy, int textureWidth, int textureHeight, SDL_RendererFlip flip = SDL_FLIP_NONE)
    {
        X = posx;
        Y = posy;
        Flip = flip;
        Width = textureWidth;
        Height = textureHeight;
        TextureID = textureID;
    }
    
    float X, Y;
    int Width, Height;
    std::string TextureID;
    SDL_RendererFlip Flip;
};

class GameObject : public IObject
{
public:
    GameObject(Properties* properties)
    {
        m_Transform = new Transform(properties->X, properties->Y);
        m_TextureID = properties->TextureID;
        m_Width = properties->Width;
        m_Height = properties->Height;
        m_Flip = properties->Flip;
    }
    
    virtual void Draw() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Clean() = 0;
    
protected:
    Transform* m_Transform;
    int m_Width, m_Height;
    std::string m_TextureID;
    SDL_RendererFlip m_Flip;
};
