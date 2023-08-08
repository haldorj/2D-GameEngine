#pragma once

#include "SDL.h"
#include "../Map/GameMap.h"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 640

class Engine
{
public:
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
    Engine() {}
    bool m_IsRunning = true;

    GameMap* m_LevelMap;
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
    static Engine* s_Instance;
};
