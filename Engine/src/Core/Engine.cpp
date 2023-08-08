#include "Engine.h"

#include <SDL_image.h>
#include <glm/glm.hpp>

#include "../Physics/Transform.h"
#include "../Graphics/TextureManager.h"
#include "../Characters/Knight.h"
#include "../Inputs/Input.h"
#include "../Timer/Timer.h"
#include "../Map/MapParser.h"
#include "../Camera/Camera.h"

Engine* Engine::s_Instance = nullptr;
Knight* player = nullptr;

void Engine::Init()
{

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    }

    SDL_WindowFlags window = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    
    m_Window = SDL_CreateWindow(
        "Window",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        window
    );

    if (m_Window == nullptr) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        SDL_Quit();
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
    if (m_Renderer == nullptr)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(m_Window);
        SDL_Quit();
    }

    if (MapParser::GetInstance()->Load())
        m_LevelMap = MapParser::GetInstance()->GetMap("map");
    else
        std::cout << "Failed to load map." << std::endl;
    

    TextureManager::GetInstance()->Load("player", "Assets/Textures/char_blue_1.png");
    TextureManager::GetInstance()->Load("bg", "Assets/Backgrounds/BG.png");
    player = new Knight(new Properties("player", 100, 200, 56, 56));
    
    m_IsRunning = true;
}

bool Engine::Clean()
{
    TextureManager::GetInstance()->Clean();
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    IMG_Quit();
    SDL_Quit();
    
    return true;
}

void Engine::Quit()
{
    m_IsRunning = false;
}

void Engine::Update()
{
    float deltaTime = Timer::GetInstance()->GetDeltaTime();
    player->Update(deltaTime);
    m_LevelMap->Update();
    Camera::GetInstance()->SetTarget(player->GetOrigin());
    Camera::GetInstance()->Update(deltaTime);
}

void Engine::Render()
{
    SDL_SetRenderDrawColor(m_Renderer, 124, 210, 254, 255);

    
    SDL_RenderClear(m_Renderer);
    TextureManager::GetInstance()->Draw("bg", 0,0,1920,640);

    m_LevelMap->Render();
    player->Draw();

    SDL_RenderPresent(m_Renderer);
}

void Engine::Events()
{
    Input::GetInstance()->HandleEvents();
}
