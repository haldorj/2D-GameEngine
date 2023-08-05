#include "RenderWindow.h"


#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

RenderWindow::RenderWindow()
{
    CreateWindow(WIDTH, HEIGHT);
}

RenderWindow::RenderWindow(int width, int height)
{
    CreateWindow(width, height);
}

void RenderWindow::Update()
{
    //m_Player = new Entity();

    // Initialize random seed
    srand(time(NULL));

    for (int i = 0; i < 10; i++)
    {
        int w = rand() % 700 + 0;
        int h = rand() % 500 + 0;

        // Create an entity
        Entity entity;

        // Create and add components
        TransformComponent* transform = new TransformComponent();
        transform->Position = glm::vec2(w, h);
        entity.AddComponent(transform);

        SpriteComponent* sprite = new SpriteComponent();
        sprite->Sprite = new Texture(m_Renderer, "../Textures/tex.png");
        entity.AddComponent(sprite); 

        m_Entities.push_back(entity);
    }
}

void RenderWindow::Render()
{
    while (!m_Quit)
    {
        while (SDL_PollEvent(&m_Event))
        {
            if (m_Event.type == SDL_QUIT)
            {
                m_Quit = true;
            }
            ReadInput();

            SDL_RenderClear(m_Renderer); // Clear the renderer with the selected color
            // Render your content here
            m_RenderSystem.Update(m_Entities);
            m_NPCMovementSystem.Update(m_Entities);

            SDL_RenderPresent(m_Renderer); // Present the renderer
            // You can add your rendering and game logic here
        }
    }
}

void RenderWindow::ReadInput()
{
    // Read sdl events
    SDL_PollEvent(&m_Event);
    // Get all keys here
    const Uint8* keystates = SDL_GetKeyboardState(NULL);

    // Quit / close our window by pressing escape
    if (keystates[SDL_SCANCODE_ESCAPE]) 
    {
        m_Quit = true;
    }
    
    //if (m_Player != nullptr)
    //{
    //    if (m_Event.type == SDL_KEYDOWN) {
    //        switch (m_Event.key.keysym.sym) {
    //        case SDLK_UP:
    //            // Update KeyInputComponent for "up" key
    //            m_Player->GetComponent<KeyInputComponent>()->upKey = true;
    //            break;
    //            // Handle other key events similarly
    //        }
    //    }
    //    if (m_Event.type == SDL_KEYUP) {
    //        switch (m_Event.key.keysym.sym) {
    //        case SDLK_UP:
    //            // Update KeyInputComponent for "up" key release
    //            m_Player->GetComponent<KeyInputComponent>()->upKey = false;
    //            break;
    //            // Handle other key events similarly
    //        }
    //    }
    //}

}

void RenderWindow::CreateWindow(int width, int height)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    }

    m_Window = SDL_CreateWindow(
        "SDL2 Window",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN
    );

    if (m_Window == nullptr) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        SDL_Quit();
    }

    CreateRenderer();
}

void RenderWindow::CreateRenderer()
{
    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
    if (m_Renderer == nullptr)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(m_Window);
        SDL_Quit();
    }
    //SDL_SetRenderDrawColor(m_Renderer, 255, 0, 0, 255);
}

RenderWindow::~RenderWindow()
{
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}