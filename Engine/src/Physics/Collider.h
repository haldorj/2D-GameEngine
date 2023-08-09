#pragma once
#include <SDL.h>
#include "../Camera/Camera.h"
class Collider
{
public:
    SDL_Rect GetCollider() { return m_BoxCollider; }
    void SetBuffer(int x, int y, int w, int h) { m_Buffer = {x, y, w, h}; }

    void SetCollider(int x, int y, int w, int h)
    {
        m_BoxCollider = {
            x - m_Buffer.x,
            y - m_Buffer.y,
            w - m_Buffer.w,
            h - m_Buffer.h
        };
    }

    void DrawDebugRect()
    {
        glm::vec2 camera = Camera::GetInstance()->GetPosition();
        m_BoxCollider.x -= camera.x;
        m_BoxCollider.y -= camera.y;
        SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &m_BoxCollider);
    }
    
private:
    SDL_Rect m_BoxCollider;
    SDL_Rect m_Buffer;
};
 