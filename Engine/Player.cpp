#include "Player.h"

Player::Player(SDL_Renderer* renderer)
{
    // Create components and assign them to member variables
    m_Sprite = new SpriteComponent();
    m_Sprite->Sprite = new Texture(renderer, "../Textures/player.png");

    m_Transform = new TransformComponent();
    m_Transform->Position.x = 100.0f;
    m_Transform->Position.y = 100.0f;

    m_Velocity = new VelocityComponent();
    m_Velocity->Velocity.x = 1.0f;
    m_Velocity->Velocity.y = 1.0f;

    m_KeyInput = new KeyInputComponent();

    // Add the components to the entity
    AddComponent(m_Sprite);
    AddComponent(m_Transform);
    AddComponent(m_Velocity);
    AddComponent(m_KeyInput);
}

void Player::HandleInput(const Uint8* keystates)
{
    // Update the player's movement state based on keys

    if (keystates[SDL_SCANCODE_A]) { m_MovementState.x -= m_Velocity->Velocity.x; }
    if (keystates[SDL_SCANCODE_D]) { m_MovementState.x += m_Velocity->Velocity.x; }
    if (keystates[SDL_SCANCODE_W]) { m_MovementState.y -= m_Velocity->Velocity.y; }
    if (keystates[SDL_SCANCODE_S]) { m_MovementState.y += m_Velocity->Velocity.y; }
}

void Player::Update(float deltaTime)
{
    // Update player's position based on movement state and delta time
    m_Transform->Position.x += m_MovementState.x * deltaTime;
    m_Transform->Position.y += m_MovementState.y * deltaTime;

    m_MovementState = { 0.0f, 0.0f };

    if (m_Transform->Position.x <= 0)
    {
        m_Transform->Position.x = 0;
    }
    if (m_Transform->Position.x >= 740)
    {
        m_Transform->Position.x = 740;
    }
    if (m_Transform->Position.y <= 0)
    {
        m_Transform->Position.y = 0;
    }
    if (m_Transform->Position.y >= 540)
    {
        m_Transform->Position.y = 540;
    }
}