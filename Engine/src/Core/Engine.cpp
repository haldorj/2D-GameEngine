#include "Engine.h"

#include <SDL_image.h>
#include <glm/glm.hpp>

#include "../Physics/Transform.h"
#include "../Graphics/TextureManager.h"
#include "../Characters/Knight.h"
#include "../Inputs/Input.h"
#include "../Timer/Timer.h"

Engine* Engine::s_Instance = nullptr;
Knight* player = nullptr;

void Engine::Init()
{

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    }

    m_Window = SDL_CreateWindow(
        "Window",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
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

    TextureManager::GetInstance()->Load("player", "Assets/Textures/char_blue_1.png");
    player = new Knight(new Properties("player", 100, 200, 56, 56));
    
    Transform tf;
    tf.Log();
    
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
}

void Engine::Render()
{
    SDL_SetRenderDrawColor(m_Renderer, 124, 210, 254, 255);

    SDL_RenderClear(m_Renderer);

    player->Draw();

    SDL_RenderPresent(m_Renderer);
}

void Engine::Events()
{
    Input::GetInstance()->HandleEvents();
}
