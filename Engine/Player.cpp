#include "Player.h"

Player::Player(SDL_Renderer* renderer)
{
    // Create components and assign them to member variables
    m_Sprite = new SpriteComponent();
    m_Sprite->Sprite = new Texture(renderer, "../Textures/player.png");

    m_Transform = new TransformComponent();
    m_Transform->Position.x = 100.0f;
    m_Transform->Position.y = 100.0f;

    m_Movement = new MovementComponent();
    m_Movement->Velocity.x = Speed; m_Movement->Velocity.y = Speed;

    m_KeyInput = new KeyInputComponent();

    // Add the components to the entity
    AddComponent(m_Sprite);
    AddComponent(m_Transform);
    AddComponent(m_Movement);
    AddComponent(m_KeyInput);
}

void Player::HandleInput(const Uint8* keystates)
{
    // Update the player's velocity based on keys

    if (keystates[SDL_SCANCODE_A]) { m_Movement->Velocity.x = -Speed; }
    else if (keystates[SDL_SCANCODE_D]) { m_Movement->Velocity.x = Speed; }
    else { m_Movement->Velocity.x = 0.0f; }

    if (keystates[SDL_SCANCODE_SPACE] && IsOnGround)
    {
        m_Movement->Velocity.y = -JumpForce;
        IsJumping = true;
        IsOnGround = false;
    }
}

void Player::Update(float deltaTime)
{
    // Apply gravity for falling if not jumping and not on ground
    if (!IsOnGround && !IsJumping)
    {
        m_Movement->Velocity.y += Gravity * deltaTime;
        IsFalling = true;
    }

    // Update player's position based on velocity and delta time
    m_Transform->Position.x += m_Movement->Velocity.x * deltaTime;
    m_Transform->Position.y += m_Movement->Velocity.y * deltaTime;

    // Boundaries check
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

    if (m_Transform->Position.y >= 500)
    {
        m_Transform->Position.y = 500;
        m_Movement->Velocity.y = 0;
        IsJumping = false;
        IsFalling = false;
        IsOnGround = true;
    }

    // Handle jumping logic
    if (IsJumping)
    {
        float timer = 0.5f;
        timer -= deltaTime;
        if (timer <= 0)
        {
            IsJumping = false;
        }
    }
}