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
    m_Player = new Player(m_Renderer);
    m_Entities.push_back(*m_Player);


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
    Uint64 currentTime = SDL_GetPerformanceCounter();
    Uint64 lastTime = 0;
    double deltaTime = 0.0;

    while (!m_Quit)
    {
        lastTime = currentTime;
        currentTime = SDL_GetPerformanceCounter();

        deltaTime = static_cast<double>((currentTime - lastTime) * 1000) / SDL_GetPerformanceFrequency();

        ReadInput(deltaTime);  // Move input handling out of the event loop

        SDL_RenderClear(m_Renderer);
        m_RenderSystem.Update(m_Entities);
        m_NPCMovementSystem.Update(m_Entities);

        SDL_RenderPresent(m_Renderer);

        // Update player's movement every frame
        m_Player->Update(deltaTime);

        // Handle any pending SDL events
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                m_Quit = true;
            }
        }
    }
}

void RenderWindow::ReadInput(float deltaTime)
{
    const Uint8* keystates = SDL_GetKeyboardState(NULL);

    // Quit / close the window by pressing escape
    if (keystates[SDL_SCANCODE_ESCAPE])
    {
        m_Quit = true;
    }

    if (m_Player)
    {
        m_Player->HandleInput(keystates, deltaTime);
    }
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
    SDL_SetRenderDrawColor(m_Renderer, 50, 0, 100, 255);
}

RenderWindow::~RenderWindow()
{
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}