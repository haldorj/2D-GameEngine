#pragma once

#include "SDL.h"
#include "../Map/GameMap.h"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 640

class Engine
{
public:
    static Engine* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Engine(); }
    
    void Init();
    bool Clean();
    void Quit();

    void Update();
    void Render();
    void Events();

    GameMap* GetMap() { return m_LevelMap; }
    bool IsRunning() const { return m_IsRunning; }
    SDL_Renderer* GetRenderer() { return m_Renderer; }
    
private:
    Engine() {}
    bool m_IsRunning = true;

    GameMap* m_LevelMap;
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
    static Engine* s_Instance;
};
