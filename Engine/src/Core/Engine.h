#pragma once

#include "SDL.h"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 640

class Engine
{
public:
    Engine() {}
    
    void Init();
    bool Clean();
    void Quit();

    void Update();
    void Render();
    void Events();

    bool IsRunning() const { return m_IsRunning; }

    static Engine* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Engine(); }
    SDL_Renderer* GetRenderer() { return m_Renderer; }
    
private:
    bool m_IsRunning = true;
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
    static Engine* s_Instance;
};
